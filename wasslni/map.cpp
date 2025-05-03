#include "Map.h"
#include "Options.h"  // ✅ تضمين ملف نافذة Options

#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <QDebug>
#include <QFile>
#include <QTextStream>

Map::Map(QWidget *parent) : QWidget(parent)
{
    setFixedSize(600, 500);
    setWindowTitle("Map");

    // إعداد الخلفية
    QPixmap background("C:/Users/A/OneDrive/Documents/wasslni/images/Screenshot 2025-04-28 183435.png");
    if (background.isNull()) {
        qDebug() << "Failed to load background image.";
        background = QPixmap(600, 500);
        background.fill(Qt::lightGray);
    }

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);

    // إعداد عناصر الواجهة
    QLabel *title = new QLabel("Add number of edges", this);
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: black;");
    title->setAlignment(Qt::AlignCenter);

    edgeCountField = new QLineEdit(this);
    edgeCountField->setPlaceholderText("Enter number of edges");
    edgeCountField->setStyleSheet("padding: 8px; font-size: 14px;");

    submitButton = new QPushButton("Submit", this);
    submitButton->setStyleSheet("padding: 8px; background-color: gray; color: white; font-weight: bold;");
    connect(submitButton, &QPushButton::clicked, this, &Map::onSubmitEdgeCount);

    continueButton = new QPushButton("Continue", this);
    continueButton->setStyleSheet("padding: 8px; background-color: #4CAF50; color: white; font-weight: bold;");
    connect(continueButton, &QPushButton::clicked, this, &Map::onContinueClicked);
    continueButton->show();

    // Scroll Area
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    QWidget *scrollContent = new QWidget(scrollArea);
    inputsLayout = new QVBoxLayout(scrollContent);
    scrollContent->setLayout(inputsLayout);
    scrollArea->setWidget(scrollContent);
    scrollArea->hide();

    // زر حفظ البيانات
    saveButton = new QPushButton("Save", this);
    saveButton->setStyleSheet("padding: 8px; background-color: #4CAF50; color: white; font-weight: bold;");
    connect(saveButton, &QPushButton::clicked, this, &Map::onSaveClicked);
    saveButton->hide();

    // تخطيط المحتوى المتغير
    QVBoxLayout *contentLayout = new QVBoxLayout();
    contentLayout->addWidget(title);
    contentLayout->addWidget(edgeCountField);
    contentLayout->addWidget(submitButton);
    contentLayout->addWidget(scrollArea);
    contentLayout->addWidget(saveButton);

    // التخطيط الرئيسي
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(contentLayout);
    mainLayout->addStretch();  // يضمن أن زر Continue يثبت في الأسفل
    mainLayout->addWidget(continueButton);
    mainLayout->setContentsMargins(50, 30, 50, 30);
    setLayout(mainLayout);
}

void Map::onSubmitEdgeCount()
{
    bool ok;
    int count = edgeCountField->text().toInt(&ok);

    if (!ok || count <= 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid number of edges.");
        return;
    }

    // تفريغ المدخلات القديمة
    QLayoutItem *child;
    while ((child = inputsLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    edgeInputs.clear();

    // إنشاء المدخلات حسب العدد
    for (int i = 0; i < count; ++i) {
        QHBoxLayout *row = new QHBoxLayout();
        QLineEdit *cityA = new QLineEdit();
        QLineEdit *cityB = new QLineEdit();
        QLineEdit *distance = new QLineEdit();

        cityA->setPlaceholderText("City A");
        cityB->setPlaceholderText("City B");
        distance->setPlaceholderText("Distance");

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
    QMessageBox::information(this, "Success", "Edges saved successfully!");
}

void Map::saveGraphData(const QVector<std::tuple<QString, QString, int>> &edges)
{
    QString filePath = "C:/Users/A/OneDrive/Documents/wasslni/graph.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open graph file.");
        return;
    }

    QTextStream out(&file);
    for (const auto& edge : edges) {
        out << std::get<0>(edge) << "," << std::get<1>(edge) << "," << std::get<2>(edge) << "\n";
    }

    file.close();
}

void Map::onContinueClicked()
{
    // ✅ فتح نافذة Options
    Options *optionsWindow = new Options();
    optionsWindow->show();

    // إغلاق نافذة Map
    this->close();
}
