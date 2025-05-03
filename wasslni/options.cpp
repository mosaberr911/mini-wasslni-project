#include "options.h"
#include "graph.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QSpacerItem>

Options::Options(QWidget *parent) : QWidget(parent)
{
    setFixedSize(600, 700);
    setWindowTitle("Options");

    // الخلفية
    QPixmap background("C:/Users/A/OneDrive/Documents/wasslni/images/Screenshot 2025-04-28 183435.png");
    if (background.isNull()) {
        qDebug() << "Failed to load background image.";
        background = QPixmap(600, 700);
        background.fill(Qt::lightGray);
    }

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);

    // Layout رئيسي
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(100, 30, 100, 30);  // هوامش داخلية

    // إعدادات الحجم والخط
    int elementHeight = 50;
    int elementWidth = 350;
    QFont font;
    font.setPointSize(12);

    // زر Show Shortest Path
    showShortestPathButton = new QPushButton("Show Shortest Path");
    showShortestPathButton->setStyleSheet("background-color: green; color: white;");
    showShortestPathButton->setFixedSize(elementWidth, elementHeight);
    showShortestPathButton->setFont(font);
    mainLayout->addWidget(showShortestPathButton, 0, Qt::AlignHCenter);

    // حقول إدخال المدن
    startCityLineEdit = new QLineEdit();
    startCityLineEdit->setPlaceholderText("Enter Start City");
    startCityLineEdit->setVisible(false);
    startCityLineEdit->setFixedSize(elementWidth, elementHeight);
    startCityLineEdit->setFont(font);
    mainLayout->addWidget(startCityLineEdit, 0, Qt::AlignHCenter);

    endCityLineEdit = new QLineEdit();
    endCityLineEdit->setPlaceholderText("Enter End City");
    endCityLineEdit->setVisible(false);
    endCityLineEdit->setFixedSize(elementWidth, elementHeight);
    endCityLineEdit->setFont(font);
    mainLayout->addWidget(endCityLineEdit, 0, Qt::AlignHCenter);

    // زر Show Path
    showPathButton = new QPushButton("Show Path");
    showPathButton->setStyleSheet("background-color: green; color: white;");
    showPathButton->setVisible(false);
    showPathButton->setEnabled(false);
    showPathButton->setFixedSize(elementWidth, elementHeight);
    showPathButton->setFont(font);
    mainLayout->addWidget(showPathButton, 0, Qt::AlignHCenter);

    // زر Display Map
    displayMapButton = new QPushButton("Display Map");
    displayMapButton->setStyleSheet("background-color: green; color: white;");
    displayMapButton->setFixedSize(elementWidth, elementHeight);
    displayMapButton->setFont(font);
    mainLayout->addWidget(displayMapButton, 0, Qt::AlignHCenter);

    // زر Add City
    addCityButton = new QPushButton("Add City");
    addCityButton->setStyleSheet("background-color: green; color: white;");
    addCityButton->setFixedSize(elementWidth, elementHeight);
    addCityButton->setFont(font);
    mainLayout->addWidget(addCityButton, 0, Qt::AlignHCenter);

    // حقل إضافة مدينة
    addCityLineEdit = new QLineEdit();
    addCityLineEdit->setPlaceholderText("Enter City Name");
    addCityLineEdit->setVisible(false);
    addCityLineEdit->setFixedSize(elementWidth, elementHeight);
    addCityLineEdit->setFont(font);
    mainLayout->addWidget(addCityLineEdit, 0, Qt::AlignHCenter);

    // ربط الإشارات بالأحداث
    connect(showShortestPathButton, &QPushButton::clicked, this, &Options::onShowShortestPathClicked);
    connect(showPathButton, &QPushButton::clicked, this, &Options::onShowPathClicked);
    connect(displayMapButton, &QPushButton::clicked, this, &Options::onDisplayMapClicked);
    connect(addCityButton, &QPushButton::clicked, this, &Options::onAddCityClicked);
}

void Options::onShowShortestPathClicked()
{
    isPathInputVisible = !isPathInputVisible;

    startCityLineEdit->setVisible(isPathInputVisible);
    endCityLineEdit->setVisible(isPathInputVisible);
    showPathButton->setVisible(isPathInputVisible);
    showPathButton->setEnabled(isPathInputVisible);

    if (isPathInputVisible) {
        showShortestPathButton->setText("Hide Path Input");
    } else {
        showShortestPathButton->setText("Show Shortest Path");
    }
}

void Options::onDisplayMapClicked()
{
    Graph graph;
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");

    if (edges.isEmpty()) {
        QMessageBox::warning(this, "File Error", "No edges were loaded from the file. Please check the file format.");
        return;
    }

    try {
        graph.addGraphFromUI(edges);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", "An error occurred while adding the graph: " + QString(e.what()));
        return;
    }

    try {
        QString mapRepresentation = QString::fromStdString(graph.displayMap());
        QMessageBox::information(this, "Map Display", mapRepresentation);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", "An error occurred while displaying the map: " + QString(e.what()));
    }
}

void Options::onAddCityClicked()
{
    isAddCityInputVisible = !isAddCityInputVisible;
    addCityLineEdit->setVisible(isAddCityInputVisible);

    if (isAddCityInputVisible) {
        addCityButton->setText("Hide Add City");
    } else {
        addCityButton->setText("Add City");
    }
}

QVector<std::tuple<QString, QString, int>> Options::loadEdgesFromFile(const QString& filePath)
{
    QVector<std::tuple<QString, QString, int>> edges;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << filePath;
        return edges;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(',');
        if (parts.size() == 3) {
            QString a = parts[0].trimmed();
            QString b = parts[1].trimmed();
            int dist = parts[2].trimmed().toInt();
            edges.append({a, b, dist});
        }
    }

    file.close();
    return edges;
}

void Options::onShowPathClicked()
{
    QString startCity = startCityLineEdit->text().trimmed();
    QString endCity = endCityLineEdit->text().trimmed();

    if (startCity.isEmpty() || endCity.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Both cities must be entered!");
        return;
    }

    Graph graph;
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");
    graph.addGraphFromUI(edges);

    std::string result = graph.dijkstra(startCity.toStdString(), endCity.toStdString());
    QMessageBox::information(this, "Shortest Path", QString::fromStdString(result));
}
