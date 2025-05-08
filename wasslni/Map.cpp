#include "Map.h"
#include "Options.h"

#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <QDebug>
#include <QRegularExpression>
#include <QFile>
#include <QDir>
#include <QTextStream>

Map::Map(QWidget *parent) : QWidget(parent), userEmail(""), isSaved(false)
{
    setFixedSize(600, 500);
    setWindowTitle("Map");
    
    // SABER_PATH
    QPixmap background("C:/Users/A/OneDrive/Documents/wasslni/images/Screenshot 2025-04-28 183435.png");

    // YASSIN_PATH
    // QPixmap background("/Users/mohamed/CLionProjects/mini-wasslni-project/wasslni/images/Screenshot 2025-04-28 183435.png");
    
    if (background.isNull()) {
        qDebug() << "Failed to load background image.";
        background = QPixmap(600, 500);
        background.fill(Qt::lightGray);
    }

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);

    title = new QLabel("Add number of roads", this);
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: black;");
    title->setAlignment(Qt::AlignCenter);
    title->hide();

    edgeCountField = new QLineEdit(this);
    edgeCountField->setPlaceholderText("Enter number of roads");
    edgeCountField->setStyleSheet("padding: 8px; font-size: 14px; background-color: white; color: black;");
    edgeCountField->hide();

    submitButton = new QPushButton("Submit", this);
    submitButton->setStyleSheet("padding: 8px; background-color: gray; color: white; font-weight: bold;");
    connect(submitButton, &QPushButton::clicked, this, &Map::onSubmitEdgeCount);
    submitButton->hide();

    addMapButton = new QPushButton("Add Map", this);
    addMapButton->setStyleSheet("padding: 8px; background-color: #2196F3; color: white; font-weight: bold;");
    connect(addMapButton, &QPushButton::clicked, this, &Map::onAddMapClicked);

    continueButton = new QPushButton("Continue", this);
    continueButton->setStyleSheet("padding: 8px; background-color: #4CAF50; color: white; font-weight: bold;");
    connect(continueButton, &QPushButton::clicked, this, &Map::onContinueClicked);

    nextPageLabel = new QLabel("Go to the next page", this);
    nextPageLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");
    nextPageLabel->setAlignment(Qt::AlignCenter);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background-color: white;");

    QWidget *scrollContent = new QWidget(scrollArea);
    scrollContent->setStyleSheet("background-color: white;");

    inputsLayout = new QVBoxLayout(scrollContent);
    inputsLayout->setSpacing(10);
    inputsLayout->setContentsMargins(10, 10, 10, 10);
    scrollContent->setLayout(inputsLayout);
    scrollArea->setWidget(scrollContent);
    scrollArea->hide();

    saveButton = new QPushButton("Save", this);
    saveButton->setStyleSheet("padding: 8px; background-color: #4CAF50; color: white; font-weight: bold;");
    connect(saveButton, &QPushButton::clicked, this, &Map::onSaveClicked);
    saveButton->hide();

    QVBoxLayout *contentLayout = new QVBoxLayout();
    contentLayout->addWidget(title);
    contentLayout->addSpacing(10);
    contentLayout->addWidget(edgeCountField);
    contentLayout->addWidget(submitButton);
    contentLayout->addWidget(scrollArea);
    contentLayout->addWidget(saveButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(addMapButton);
    mainLayout->addLayout(contentLayout);
    mainLayout->addStretch();

    QVBoxLayout *bottomLayout = new QVBoxLayout();
    bottomLayout->addSpacing(20);
    bottomLayout->addWidget(nextPageLabel);
    bottomLayout->addWidget(continueButton);
    bottomLayout->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

    mainLayout->addLayout(bottomLayout);
    mainLayout->setContentsMargins(50, 10, 50, 30);
    setLayout(mainLayout);
}

void Map::setUserEmail(const QString &email)
{
    userEmail = email;
    graph.setUserEmail(email.toStdString());
}

QString Map::getUserGraphPath() const {
    QString sanitizedEmail = userEmail;
    sanitizedEmail.replace("@", "_at_");
    sanitizedEmail.replace(".", "_dot_");
    sanitizedEmail.replace(QRegularExpression("[^a-zA-Z0-9_]"), "_");

    // SABER_PATH
    QString dirPath = "C:/Users/A/OneDrive/Documents/wasslni/maps";

    // YASSIN_PATH
    // QString dirPath = "/Users/mohamed/CLionProjects/mini-wasslni-project/wasslni/maps";
    
    QDir dir(dirPath);

    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qDebug() << "Failed to create maps directory";
            return "";
        }
    }

    return dirPath + "/" + sanitizedEmail + "_map.txt";
}

void Map::onAddMapClicked()
{
    title->show();
    edgeCountField->show();
    submitButton->show();
    addMapButton->hide();
    isSaved = false;
    saveButton->setEnabled(true); 
    saveButton->setStyleSheet("padding: 8px; background-color: #4CAF50; color: white; font-weight: bold;"); 
}

void Map::onSubmitEdgeCount()
{
    bool ok;
    int count = edgeCountField->text().toInt(&ok);

    if (!ok || count <= 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid number of roads.");
        return;
    }

    QLayoutItem *child;
    while ((child = inputsLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    edgeInputs.clear();

    for (int i = 0; i < count; ++i) {
        QHBoxLayout *row = new QHBoxLayout();
        QLineEdit *cityA = new QLineEdit();
        QLineEdit *cityB = new QLineEdit();
        QLineEdit *distance = new QLineEdit();

        cityA->setPlaceholderText("City A");
        cityB->setPlaceholderText("City B");
        distance->setPlaceholderText("Distance");

        QString inputStyle = "background-color: white; color: black; padding: 5px;";
        cityA->setStyleSheet(inputStyle);
        cityB->setStyleSheet(inputStyle);
        distance->setStyleSheet(inputStyle);

        row->addWidget(cityA);
        row->addWidget(cityB);
        row->addWidget(distance);
        inputsLayout->addLayout(row);

        edgeInputs.append({cityA, cityB, distance});
    }

    scrollArea->show();
    saveButton->show();
    submitButton->hide();
}

void Map::onSaveClicked()
{
    if (isSaved) {
        QMessageBox::information(this, "Info", "You have already saved the roads.");
        return;
    }

    QVector<std::tuple<QString, QString, int>> edges;

    for (const auto& input : edgeInputs) {
        QString a = input.cityA->text().trimmed();
        QString b = input.cityB->text().trimmed();
        int d = input.distance->text().toInt();

        if (a.isEmpty() || b.isEmpty() || d <= 0) {
            QMessageBox::warning(this, "Error", "Please fill all fields correctly.");
            return;
        }

        edges.append({a, b, d});
    }

    saveGraphData(edges);
    isSaved = true;
    saveButton->setEnabled(false);
    saveButton->setStyleSheet("padding: 8px; background-color: #cccccc; color: #666666; font-weight: bold;");

    QMessageBox::information(this, "Success", "Roads saved successfully!");
}

void Map::saveGraphData(const QVector<std::tuple<QString, QString, int>> &edges) {
    QString filePath = getUserGraphPath();
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto &edge : edges) {
            out << std::get<0>(edge) << ","
                << std::get<1>(edge) << ","
                << std::get<2>(edge) << "\n";
        }
        file.close();
    } else {
        qDebug() << "Failed to save graph data to" << filePath;
    }
}

void Map::onContinueClicked()
{
    Options *optionsWindow = new Options();
    optionsWindow->setUserEmail(userEmail);
    optionsWindow->show();
    this->close();
}
