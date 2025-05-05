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
    setFixedSize(600, 700); // Increased height to accommodate new button
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
    mainLayout->setContentsMargins(100, 30, 100, 30);

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

    // زر Save City
    saveCityButton = new QPushButton("Save City");
    saveCityButton->setStyleSheet("background-color: green; color: white;");
    saveCityButton->setFixedSize(elementWidth, elementHeight);
    saveCityButton->setFont(font);
    saveCityButton->setVisible(false);
    mainLayout->addWidget(saveCityButton, 0, Qt::AlignHCenter);

    // زر Delete City
    deleteCityButton = new QPushButton("Delete City");
    deleteCityButton->setStyleSheet("background-color: green; color: white;");
    deleteCityButton->setFixedSize(elementWidth, elementHeight);
    deleteCityButton->setFont(font);
    mainLayout->addWidget(deleteCityButton, 0, Qt::AlignHCenter);

    // حقل إدخال حذف المدينة
    deleteCityLineEdit = new QLineEdit();
    deleteCityLineEdit->setPlaceholderText("Enter City Name");
    deleteCityLineEdit->setVisible(false);
    deleteCityLineEdit->setFixedSize(elementWidth, elementHeight);
    deleteCityLineEdit->setFont(font);
    mainLayout->addWidget(deleteCityLineEdit, 0, Qt::AlignHCenter);

    // زر Confirm Delete City
    confirmDeleteCityButton = new QPushButton("Confirm Delete");
    confirmDeleteCityButton->setStyleSheet("background-color: green; color: white;");
    confirmDeleteCityButton->setFixedSize(elementWidth, elementHeight);
    confirmDeleteCityButton->setFont(font);
    confirmDeleteCityButton->setVisible(false);
    mainLayout->addWidget(confirmDeleteCityButton, 0, Qt::AlignHCenter);

    // زر Add Road
    addRoadButton = new QPushButton("Add Road");
    addRoadButton->setStyleSheet("background-color: green; color: white;");
    addRoadButton->setFixedSize(elementWidth, elementHeight);
    addRoadButton->setFont(font);
    mainLayout->addWidget(addRoadButton, 0, Qt::AlignHCenter);

    // حقول إدخال الطريق
    roadStartCityLineEdit = new QLineEdit();
    roadStartCityLineEdit->setPlaceholderText("Start City");
    roadStartCityLineEdit->setVisible(false);
    roadStartCityLineEdit->setFixedSize(elementWidth, elementHeight);
    roadStartCityLineEdit->setFont(font);
    mainLayout->addWidget(roadStartCityLineEdit, 0, Qt::AlignHCenter);

    roadEndCityLineEdit = new QLineEdit();
    roadEndCityLineEdit->setPlaceholderText("End City");
    roadEndCityLineEdit->setVisible(false);
    roadEndCityLineEdit->setFixedSize(elementWidth, elementHeight);
    roadEndCityLineEdit->setFont(font);
    mainLayout->addWidget(roadEndCityLineEdit, 0, Qt::AlignHCenter);

    roadDistanceLineEdit = new QLineEdit();
    roadDistanceLineEdit->setPlaceholderText("Distance");
    roadDistanceLineEdit->setVisible(false);
    roadDistanceLineEdit->setFixedSize(elementWidth, elementHeight);
    roadDistanceLineEdit->setFont(font);
    mainLayout->addWidget(roadDistanceLineEdit, 0, Qt::AlignHCenter);

    // زر Save Road
    saveRoadButton = new QPushButton("Save Road");
    saveRoadButton->setStyleSheet("background-color: green; color: white;");
    saveRoadButton->setFixedSize(elementWidth, elementHeight);
    saveRoadButton->setFont(font);
    saveRoadButton->setVisible(false);
    mainLayout->addWidget(saveRoadButton, 0, Qt::AlignHCenter);

    // زر Delete Road
    deleteRoadButton = new QPushButton("Delete Road");
    deleteRoadButton->setStyleSheet("background-color: green; color: white;");
    deleteRoadButton->setFixedSize(elementWidth, elementHeight);
    deleteRoadButton->setFont(font);
    mainLayout->addWidget(deleteRoadButton, 0, Qt::AlignHCenter);

    // حقول إدخال حذف الطريق
    deleteStartCityLineEdit = new QLineEdit();
    deleteStartCityLineEdit->setPlaceholderText("Start City");
    deleteStartCityLineEdit->setVisible(false);
    deleteStartCityLineEdit->setFixedSize(elementWidth, elementHeight);
    deleteStartCityLineEdit->setFont(font);
    mainLayout->addWidget(deleteStartCityLineEdit, 0, Qt::AlignHCenter);

    deleteEndCityLineEdit = new QLineEdit();
    deleteEndCityLineEdit->setPlaceholderText("End City");
    deleteEndCityLineEdit->setVisible(false);
    deleteEndCityLineEdit->setFixedSize(elementWidth, elementHeight);
    deleteEndCityLineEdit->setFont(font);
    mainLayout->addWidget(deleteEndCityLineEdit, 0, Qt::AlignHCenter);

    // زر Confirm Delete
    confirmDeleteButton = new QPushButton("Confirm Delete");
    confirmDeleteButton->setStyleSheet("background-color: green; color: white;");
    confirmDeleteButton->setFixedSize(elementWidth, elementHeight);
    confirmDeleteButton->setFont(font);
    confirmDeleteButton->setVisible(false);
    mainLayout->addWidget(confirmDeleteButton, 0, Qt::AlignHCenter);

    // ربط الإشارات بالأحداث
    connect(showShortestPathButton, &QPushButton::clicked, this, &Options::onShowShortestPathClicked);
    connect(showPathButton, &QPushButton::clicked, this, &Options::onShowPathClicked);
    connect(displayMapButton, &QPushButton::clicked, this, &Options::onDisplayMapClicked);
    connect(addCityButton, &QPushButton::clicked, this, &Options::onAddCityClicked);
    connect(saveCityButton, &QPushButton::clicked, this, &Options::onSaveCityClicked);
    connect(deleteCityButton, &QPushButton::clicked, this, &Options::onDeleteCityClicked);
    connect(confirmDeleteCityButton, &QPushButton::clicked, this, &Options::onConfirmDeleteCityClicked);
    connect(addRoadButton, &QPushButton::clicked, this, &Options::onAddRoadClicked);
    connect(saveRoadButton, &QPushButton::clicked, this, &Options::onSaveRoadClicked);
    connect(deleteRoadButton, &QPushButton::clicked, this, &Options::onDeleteRoadClicked);
    connect(confirmDeleteButton, &QPushButton::clicked, this, &Options::onConfirmDeleteClicked);
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
    saveCityButton->setVisible(isAddCityInputVisible);

    if (isAddCityInputVisible) {
        addCityButton->setText("Hide Add City");
    } else {
        addCityButton->setText("Add City");
    }
}

void Options::onSaveCityClicked()
{
    QString cityName = addCityLineEdit->text().trimmed();

    if (!cityName.isEmpty()) {
        Graph graph;
        QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");
        graph.addGraphFromUI(edges);

        bool cityExists = graph.containsCity(cityName.toStdString());

        if (cityExists) {
            QMessageBox::warning(this, "City Exists", "The city '" + cityName + "' already exists in the graph.");
            return;
        }

        bool cityAdded = graph.addCity(cityName.toStdString());

        if (cityAdded) {
            QMessageBox::information(this, "City Added", "City '" + cityName + "' has been saved to the graph.");
            saveCityToFile(cityName);
        } else {
            QMessageBox::warning(this, "City Add Error", "Failed to add the city '" + cityName + "' to the graph.");
        }
    } else {
        QMessageBox::warning(this, "Input Error", "Please enter a city name.");
    }
}

void Options::onDeleteCityClicked()
{
    isDeleteCityInputVisible = !isDeleteCityInputVisible;
    deleteCityLineEdit->setVisible(isDeleteCityInputVisible);
    confirmDeleteCityButton->setVisible(isDeleteCityInputVisible);

    if (isDeleteCityInputVisible) {
        deleteCityButton->setText("Hide Delete City");
    } else {
        deleteCityButton->setText("Delete City");
    }
}

void Options::onConfirmDeleteCityClicked()
{
    QString cityName = deleteCityLineEdit->text().trimmed();

    if (cityName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a city name.");
        return;
    }

    Graph graph;
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");
    graph.addGraphFromUI(edges);

    if (!graph.containsCity(cityName.toStdString())) {
        QMessageBox::warning(this, "City Error", "City '" + cityName + "' does not exist!");
        return;
    }

    bool cityDeleted = graph.deleteCity(cityName.toStdString());

    if (cityDeleted) {
        updateFileAfterCityDeletion(cityName);
        QMessageBox::information(this, "Success", "City '" + cityName + "' has been deleted successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete city '" + cityName + "'.");
    }
}

void Options::onAddRoadClicked()
{
    isAddRoadInputVisible = !isAddRoadInputVisible;

    roadStartCityLineEdit->setVisible(isAddRoadInputVisible);
    roadEndCityLineEdit->setVisible(isAddRoadInputVisible);
    roadDistanceLineEdit->setVisible(isAddRoadInputVisible);
    saveRoadButton->setVisible(isAddRoadInputVisible);

    if (isAddRoadInputVisible) {
        addRoadButton->setText("Hide Road Input");
    } else {
        addRoadButton->setText("Add Road");
    }
}

void Options::onSaveRoadClicked()
{
    QString startCity = roadStartCityLineEdit->text().trimmed();
    QString endCity = roadEndCityLineEdit->text().trimmed();
    QString distanceStr = roadDistanceLineEdit->text().trimmed();

    if (startCity.isEmpty() || endCity.isEmpty() || distanceStr.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled!");
        return;
    }

    bool ok;
    int distance = distanceStr.toInt(&ok);
    if (!ok || distance <= 0) {
        QMessageBox::warning(this, "Input Error", "Distance must be a positive number!");
        return;
    }

    if (startCity == endCity) {
        QMessageBox::warning(this, "Input Error", "Start city and end city cannot be the same!");
        return;
    }

    Graph graph;
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");
    graph.addGraphFromUI(edges);

    if (!graph.containsCity(startCity.toStdString())) {
        QMessageBox::warning(this, "City Error", "Start city '" + startCity + "' does not exist!");
        return;
    }

    if (!graph.containsCity(endCity.toStdString())) {
        QMessageBox::warning(this, "City Error", "End city '" + endCity + "' does not exist!");
        return;
    }

    bool roadAdded = graph.addEdge(startCity.toStdString(), endCity.toStdString(), distance);

    if (roadAdded) {
        saveRoadToFile(startCity, endCity, distance);
        QMessageBox::information(this, "Success", "Road between " + startCity + " and " + endCity + " has been added successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to add road. The road may already exist.");
    }
}

void Options::onDeleteRoadClicked()
{
    isDeleteRoadInputVisible = !isDeleteRoadInputVisible;

    deleteStartCityLineEdit->setVisible(isDeleteRoadInputVisible);
    deleteEndCityLineEdit->setVisible(isDeleteRoadInputVisible);
    confirmDeleteButton->setVisible(isDeleteRoadInputVisible);

    if (isDeleteRoadInputVisible) {
        deleteRoadButton->setText("Hide Delete Input");
    } else {
        deleteRoadButton->setText("Delete Road");
    }
}

void Options::onConfirmDeleteClicked()
{
    QString startCity = deleteStartCityLineEdit->text().trimmed();
    QString endCity = deleteEndCityLineEdit->text().trimmed();

    if (startCity.isEmpty() || endCity.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Both cities must be entered!");
        return;
    }

    if (startCity == endCity) {
        QMessageBox::warning(this, "Input Error", "Start city and end city cannot be the same!");
        return;
    }

    Graph graph;
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");
    graph.addGraphFromUI(edges);

    if (!graph.containsCity(startCity.toStdString())) {
        QMessageBox::warning(this, "City Error", "Start city '" + startCity + "' does not exist!");
        return;
    }

    if (!graph.containsCity(endCity.toStdString())) {
        QMessageBox::warning(this, "City Error", "End city '" + endCity + "' does not exist!");
        return;
    }

    bool roadDeleted = graph.deleteEdge(startCity.toStdString(), endCity.toStdString());

    if (roadDeleted) {
        updateFileAfterDeletion(startCity, endCity);
        QMessageBox::information(this, "Success", "Road between " + startCity + " and " + endCity + " has been deleted successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete road. The road may not exist.");
    }
}

void Options::saveCityToFile(const QString& cityName)
{
    QFile file("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "File Error", "Failed to open file for writing.");
        return;
    }

    QTextStream out(&file);
    out << cityName << ", ,10\n";
    file.close();
}

void Options::saveRoadToFile(const QString& city1, const QString& city2, int distance)
{
    QFile file("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "File Error", "Failed to open file for writing.");
        return;
    }

    QTextStream out(&file);
    out << city1 << "," << city2 << "," << distance << "\n";
    file.close();
}

void Options::updateFileAfterDeletion(const QString& city1, const QString& city2)
{
    QFile file("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "File Error", "Failed to open file for reading.");
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (parts.size() >= 2) {
            QString a = parts[0].trimmed();
            QString b = parts[1].trimmed();
            if (!(a == city1 && b == city2) && !(a == city2 && b == city1)) {
                lines.append(line);
            }
        }
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "File Error", "Failed to open file for writing.");
        return;
    }

    QTextStream out(&file);
    foreach (const QString &line, lines) {
        out << line << "\n";
    }
    file.close();
}

void Options::updateFileAfterCityDeletion(const QString& cityName)
{
    QFile file("C:/Users/A/OneDrive/Documents/wasslni/graph.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "File Error", "Failed to open file for reading.");
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (parts.size() >= 2) {
            QString a = parts[0].trimmed();
            QString b = parts[1].trimmed();
            if (a != cityName && b != cityName) {
                lines.append(line);
            }
        }
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "File Error", "Failed to open file for writing.");
        return;
    }

    QTextStream out(&file);
    foreach (const QString &line, lines) {
        out << line << "\n";
    }
    file.close();
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
            int weight = parts[2].toInt();
            edges.append(std::make_tuple(a, b, weight));
        }
    }
    return edges;
}
