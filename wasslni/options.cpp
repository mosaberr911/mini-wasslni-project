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

Options::Options(QWidget *parent) : QWidget(parent)
{
    setFixedSize(600, 500);
    setWindowTitle("Options");

    // الخلفية
    QPixmap background("C:/Users/A/OneDrive/Documents/wasslni/images/Screenshot 2025-04-28 183435.png");
    if (background.isNull()) {
        qDebug() << "Failed to load background image.";
        background = QPixmap(600, 500);
        background.fill(Qt::lightGray);
    }

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);

    // زر Show Shortest Path
    showShortestPathButton = new QPushButton("Show Shortest Path", this);
    showShortestPathButton->setStyleSheet("background-color: green; color: white;");
    showShortestPathButton->setGeometry(200, 50, 200, 40);

    // حقول إدخال المدن
    startCityLineEdit = new QLineEdit(this);
    startCityLineEdit->setPlaceholderText("Enter Start City");
    startCityLineEdit->setGeometry(150, 120, 300, 40);
    startCityLineEdit->setVisible(false);

    endCityLineEdit = new QLineEdit(this);
    endCityLineEdit->setPlaceholderText("Enter End City");
    endCityLineEdit->setGeometry(150, 180, 300, 40);
    endCityLineEdit->setVisible(false);

    // زر Show Path
    showPathButton = new QPushButton("Show Path", this);
    showPathButton->setStyleSheet("background-color: green; color: white;");
    showPathButton->setGeometry(200, 240, 200, 40);
    showPathButton->setVisible(false);
    showPathButton->setEnabled(false);

    // زر Display Map
    displayMapButton = new QPushButton("Display Map", this);
    displayMapButton->setStyleSheet("background-color: green; color: white;");
    displayMapButton->setGeometry(200, 300, 200, 40);

    // زر Add City
    addCityButton = new QPushButton("Add City", this);
    addCityButton->setStyleSheet("background-color: green; color: white;");
    addCityButton->setGeometry(200, 360, 200, 40);

    // حقل إضافة مدينة
    addCityLineEdit = new QLineEdit(this);
    addCityLineEdit->setPlaceholderText("Enter City Name");
    addCityLineEdit->setGeometry(150, 420, 300, 40);
    addCityLineEdit->setVisible(false);

    // الربط بالأحداث
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
        int centerX = (width() - startCityLineEdit->width()) / 2;
        startCityLineEdit->move(centerX, 120);
        endCityLineEdit->move(centerX, 180);
        showPathButton->move((width() - showPathButton->width()) / 2, 240);

        showShortestPathButton->setText("Hide Path Input");
    } else {
        showShortestPathButton->setText("Show Shortest Path");
    }
}

void Options::onDisplayMapClicked()
{
    // إنشاء كائن من الجراف
    Graph graph;

    // تحميل الحواف من الملف
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");

    // التأكد من أن الحواف تم تحميلها بنجاح
    if (edges.isEmpty()) {
        QMessageBox::warning(this, "File Error", "No edges were loaded from the file. Please check the file format.");
        return;  // إرجاع في حالة فشل تحميل الحواف
    }

    // إضافة الحواف إلى الجراف
    try {
        graph.addGraphFromUI(edges);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", "An error occurred while adding the graph: " + QString(e.what()));
        return;
    }

    // استدعاء دالة displayMap لعرض الخريطة
    try {
        QString mapRepresentation = QString::fromStdString(graph.displayMap());
        // عرض الخريطة في نافذة منبثقة
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
        int centerX = (width() - addCityLineEdit->width()) / 2;
        addCityLineEdit->move(centerX, 420);
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
