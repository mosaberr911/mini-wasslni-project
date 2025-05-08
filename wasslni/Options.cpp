#include "Options.h"
#include "Graph.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <QDir>
#include <QDebug>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QTextEdit>
#include <QDialog>
#include <QFileInfo>

Options::Options(QWidget *parent) : QWidget(parent), userEmail("")
{
    setFixedSize(600, 700);
    setWindowTitle("Options");

    QPixmap background("C:/Users/A/OneDrive/Documents/wasslni/images/Screenshot 2025-04-28 183435.png");
    if (background.isNull()) {
        qDebug() << "Failed to load background image.";
        background = QPixmap(600, 700);
        background.fill(Qt::lightGray);
    }

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(100, 30, 100, 30);

    int elementHeight = 50;
    int elementWidth = 350;
    QFont font;
    font.setPointSize(12);

    showShortestPathButton = new QPushButton("Show Shortest Path");
    showShortestPathButton->setStyleSheet("background-color: green; color: white;");
    showShortestPathButton->setFixedSize(elementWidth, elementHeight);
    showShortestPathButton->setFont(font);
    mainLayout->addWidget(showShortestPathButton, 0, Qt::AlignHCenter);

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

    showPathButton = new QPushButton("Show Path");
    showPathButton->setStyleSheet("background-color: green; color: white;");
    showPathButton->setVisible(false);
    showPathButton->setEnabled(false);
    showPathButton->setFixedSize(elementWidth, elementHeight);
    showPathButton->setFont(font);
    mainLayout->addWidget(showPathButton, 0, Qt::AlignHCenter);

    displayMapButton = new QPushButton("Display Map");
    displayMapButton->setStyleSheet("background-color: green; color: white;");
    displayMapButton->setFixedSize(elementWidth, elementHeight);
    displayMapButton->setFont(font);
    mainLayout->addWidget(displayMapButton, 0, Qt::AlignHCenter);

    addCityButton = new QPushButton("Add City");
    addCityButton->setStyleSheet("background-color: green; color: white;");
    addCityButton->setFixedSize(elementWidth, elementHeight);
    addCityButton->setFont(font);
    mainLayout->addWidget(addCityButton, 0, Qt::AlignHCenter);

    addCityLineEdit = new QLineEdit();
    addCityLineEdit->setPlaceholderText("Enter City Name");
    addCityLineEdit->setVisible(false);
    addCityLineEdit->setFixedSize(elementWidth, elementHeight);
    addCityLineEdit->setFont(font);
    mainLayout->addWidget(addCityLineEdit, 0, Qt::AlignHCenter);

    saveCityButton = new QPushButton("Save City");
    saveCityButton->setStyleSheet("background-color: green; color: white;");
    saveCityButton->setFixedSize(elementWidth, elementHeight);
    saveCityButton->setFont(font);
    saveCityButton->setVisible(false);
    mainLayout->addWidget(saveCityButton, 0, Qt::AlignHCenter);

    deleteCityButton = new QPushButton("Delete City");
    deleteCityButton->setStyleSheet("background-color: green; color: white;");
    deleteCityButton->setFixedSize(elementWidth, elementHeight);
    deleteCityButton->setFont(font);
    mainLayout->addWidget(deleteCityButton, 0, Qt::AlignHCenter);

    deleteCityLineEdit = new QLineEdit();
    deleteCityLineEdit->setPlaceholderText("Enter City Name");
    deleteCityLineEdit->setVisible(false);
    deleteCityLineEdit->setFixedSize(elementWidth, elementHeight);
    deleteCityLineEdit->setFont(font);
    mainLayout->addWidget(deleteCityLineEdit, 0, Qt::AlignHCenter);

    confirmDeleteCityButton = new QPushButton("Confirm Delete");
    confirmDeleteCityButton->setStyleSheet("background-color: green; color: white;");
    confirmDeleteCityButton->setFixedSize(elementWidth, elementHeight);
    confirmDeleteCityButton->setFont(font);
    confirmDeleteCityButton->setVisible(false);
    mainLayout->addWidget(confirmDeleteCityButton, 0, Qt::AlignHCenter);

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

    saveRoadButton = new QPushButton("Save Road");
    saveRoadButton->setStyleSheet("background-color: green; color: white;");
    saveRoadButton->setFixedSize(elementWidth, elementHeight);
    saveRoadButton->setFont(font);
    saveRoadButton->setVisible(false);
    mainLayout->addWidget(saveRoadButton, 0, Qt::AlignHCenter);

    deleteRoadButton = new QPushButton("Delete Road");
    deleteRoadButton->setStyleSheet("background-color: green; color: white;");
    deleteRoadButton->setFixedSize(elementWidth, elementHeight);
    deleteRoadButton->setFont(font);
    mainLayout->addWidget(deleteRoadButton, 0, Qt::AlignHCenter);

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

    confirmDeleteButton = new QPushButton("Confirm Delete");
    confirmDeleteButton->setStyleSheet("background-color: green; color: white;");
    confirmDeleteButton->setFixedSize(elementWidth, elementHeight);
    confirmDeleteButton->setFont(font);
    confirmDeleteButton->setVisible(false);
    mainLayout->addWidget(confirmDeleteButton, 0, Qt::AlignHCenter);

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

void Options::setUserEmail(const QString &email)
{
    userEmail = email;
    qDebug() << "User email set to:" << userEmail;
}

QString Options::getUserGraphPath() const
{
    if (userEmail.isEmpty()) {
        qDebug() << "Error: User email is empty!";
        return "";
    }

    QString sanitizedEmail = userEmail;
    sanitizedEmail.replace("@", "_at_");
    sanitizedEmail.replace(".", "_dot_");
    sanitizedEmail.replace(QRegularExpression("[^a-zA-Z0-9_]"), "_");

    QString dirPath = "C:/Users/A/OneDrive/Documents/wasslni/maps";
    QDir dir(dirPath);

    if (!dir.exists() && !dir.mkpath(".")) {
        qDebug() << "Failed to create maps directory";
        return "";
    }

    return dirPath + "/" + sanitizedEmail + "_map.txt";
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

    QString filePath = getUserGraphPath();
    if (filePath.isEmpty()) {
        QMessageBox::critical(this, "Error", "Cannot determine map file path");
        return;
    }

    Graph graph;
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile(filePath);
    graph.addGraphFromUI(edges);

    std::string result = graph.dijkstra(startCity.toStdString(), endCity.toStdString());
    QMessageBox::information(this, "Shortest Path", QString::fromStdString(result));
}

void Options::onDisplayMapClicked()
{
    QString filePath = getUserGraphPath();
    if (filePath.isEmpty()) {
        QMessageBox::critical(this, "Error", "Cannot determine map file path");
        return;
    }

    QFile file(filePath);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "// Map file created on " << QDateTime::currentDateTime().toString() << "\n";
            out << "// Format: city1,city2,distance\n";
            file.close();
            QMessageBox::information(this, "New Map", "Created new empty map file");
        } else {
            QMessageBox::critical(this, "Error", "Failed to create map file");
        }
        return;
    }

    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile(filePath);
    if (edges.isEmpty()) {
        QMessageBox::warning(this, "Empty Map", "Map file contains no valid data");
        return;
    }

    try {
        Graph graph;
        graph.addGraphFromUI(edges);
        QString mapContent = QString::fromStdString(graph.displayMap());

        QDialog dialog(this);
        dialog.setWindowTitle("Map Viewer - " + QFileInfo(filePath).fileName());
        dialog.resize(800, 600);

        QTextEdit *textEdit = new QTextEdit(&dialog);
        textEdit->setPlainText(mapContent);
        textEdit->setReadOnly(true);
        textEdit->setStyleSheet("font-family: Consolas, monospace; font-size: 12px;");

        QVBoxLayout layout(&dialog);
        layout.addWidget(textEdit);
        dialog.setLayout(&layout);

        dialog.exec();

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to display map: %1").arg(e.what()));
    }
}

void Options::onAddCityClicked()
{
    isAddCityInputVisible = !isAddCityInputVisible;
    addCityLineEdit->setVisible(isAddCityInputVisible);
    saveCityButton->setVisible(isAddCityInputVisible);

    if (isAddCityInputVisible) {
        addCityButton->setText("Hide City Input");
        addCityLineEdit->clear();
    } else {
        addCityButton->setText("Add City");
    }
}

void Options::onSaveCityClicked()
{
    QString cityName = addCityLineEdit->text().trimmed();
    if (cityName.isEmpty()) {
        QMessageBox::warning(this, "Error", "City name cannot be empty");
        return;
    }

    QString filePath = getUserGraphPath();
    if (filePath.isEmpty()) {
        QMessageBox::critical(this, "Error", "Cannot save city - invalid map file path");
        return;
    }

    // Load existing edges from file to check if city already exists
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile(filePath);

    // Build a set of existing cities
    QSet<QString> cities;
    for (const auto& edge : edges) {
        cities.insert(std::get<0>(edge));
        cities.insert(std::get<1>(edge));
    }

    // Check if city already exists
    if (cities.contains(cityName)) {
        QMessageBox::warning(this, "Exists", "City already exists");
        return;
    }

    // Add city to file
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open map file for writing");
        return;
    }

    QTextStream out(&file);
    if (cities.isEmpty()) {
        // If this is the first city, just add it with a placeholder
        out << cityName << "," << cityName << ",0\n";
    } else {
        // Connect new city to an existing city (first one in the set)
        QString existingCity = *cities.begin();
        out << cityName << "," << "" << ",0\n";
    }
    file.close();

    QMessageBox::information(this, "Success", "City added successfully");
    addCityLineEdit->clear();
    addCityLineEdit->setVisible(false);
    saveCityButton->setVisible(false);
    addCityButton->setText("Add City");
}

// Update the saveCityToFile method as well to be consistent
void Options::saveCityToFile(const QString& cityName)
{
    QString filePath = getUserGraphPath();
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open map file for reading");
        return;
    }

    bool isEmpty = file.size() == 0;
    file.close();

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open map file for writing");
        return;
    }

    QTextStream out(&file);
    out << cityName << ", ,0\n";
    file.close();
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
        QMessageBox::warning(this, "Error", "Please enter a city name");
        return;
    }

    QString filePath = getUserGraphPath();
    if (filePath.isEmpty()) {
        QMessageBox::critical(this, "Error", "Cannot delete city - invalid map file path");
        return;
    }

    // Load existing edges from file to check if city exists
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile(filePath);

    // Build a set of existing cities
    QSet<QString> cities;
    for (const auto& edge : edges) {
        cities.insert(std::get<0>(edge));
        cities.insert(std::get<1>(edge));
    }

    // Check if city exists
    if (!cities.contains(cityName)) {
        QMessageBox::warning(this, "Error", "City does not exist");
        return;
    }

    // Remove all edges connected to this city
    updateFileAfterCityDeletion(cityName);
    QMessageBox::information(this, "Success", "City deleted successfully");

    // Reset UI
    deleteCityLineEdit->clear();
    deleteCityLineEdit->setVisible(false);
    confirmDeleteCityButton->setVisible(false);
    deleteCityButton->setText("Delete City");
}

void Options::updateFileAfterCityDeletion(const QString& cityName)
{
    QString filePath = getUserGraphPath();
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open map file for reading");
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine();

        // Keep comments and empty lines
        if (line.trimmed().isEmpty() || line.trimmed().startsWith("//")) {
            lines.append(line);
            continue;
        }

        QStringList parts = line.split(',');
        if (parts.size() >= 2) {
            QString city1 = parts[0].trimmed();
            QString city2 = parts[1].trimmed();

            // Skip any line where either city is the one being deleted
            if (city1 == cityName || city2 == cityName) {
                continue;
            }

            lines.append(line);
        } else {
            // Keep lines with unexpected format
            lines.append(line);
        }
    }
    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open map file for writing");
        return;
    }

    QTextStream out(&file);
    foreach (const QString &line, lines) {
        out << line << "\n";
    }
    file.close();
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
        roadStartCityLineEdit->clear();
        roadEndCityLineEdit->clear();
        roadDistanceLineEdit->clear();
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
        QMessageBox::warning(this, "Error", "All fields must be filled");
        return;
    }

    bool ok;
    int distance = distanceStr.toInt(&ok);
    if (!ok || distance <= 0) {
        QMessageBox::warning(this, "Error", "Distance must be a positive number");
        return;
    }

    if (startCity == endCity) {
        QMessageBox::warning(this, "Error", "Start and end cities cannot be the same");
        return;
    }

    QString filePath = getUserGraphPath();
    if (filePath.isEmpty()) {
        QMessageBox::critical(this, "Error", "Cannot save road - invalid map file path");
        return;
    }

    // Load existing graph first to check if cities exist and if road already exists
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile(filePath);

    // Check if the road already exists
    bool roadExists = false;
    for (const auto& edge : edges) {
        QString city1 = std::get<0>(edge);
        QString city2 = std::get<1>(edge);

        if ((city1 == startCity && city2 == endCity) ||
            (city1 == endCity && city2 == startCity)) {
            roadExists = true;
            break;
        }
    }

    if (roadExists) {
        QMessageBox::warning(this, "Error", "Road already exists between these cities");
        return;
    }

    // Build a set of existing cities
    QSet<QString> cities;
    for (const auto& edge : edges) {
        cities.insert(std::get<0>(edge));
        cities.insert(std::get<1>(edge));
    }

    // Check if both cities exist
    if (!cities.contains(startCity)) {
        QMessageBox::warning(this, "Error", "Start city '" + startCity + "' does not exist");
        return;
    }

    if (!cities.contains(endCity)) {
        QMessageBox::warning(this, "Error", "End city '" + endCity + "' does not exist");
        return;
    }

    // Now add the edge to the file
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open map file for writing");
        return;
    }

    QTextStream out(&file);
    out << startCity << "," << endCity << "," << distance << "\n";
    file.close();

    QMessageBox::information(this, "Success", "Road added successfully");

    // Reset UI
    roadStartCityLineEdit->clear();
    roadEndCityLineEdit->clear();
    roadDistanceLineEdit->clear();
    roadStartCityLineEdit->setVisible(false);
    roadEndCityLineEdit->setVisible(false);
    roadDistanceLineEdit->setVisible(false);
    saveRoadButton->setVisible(false);
    addRoadButton->setText("Add Road");
}
void Options::saveRoadToFile(const QString& city1, const QString& city2, int distance)
{
    QString filePath = getUserGraphPath();
    QFile file(filePath);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open map file for writing");
        return;
    }

    QTextStream out(&file);
    out << city1 << "," << city2 << "," << distance << "\n";
    file.close();
}

void Options::onDeleteRoadClicked()
{
    isDeleteRoadInputVisible = !isDeleteRoadInputVisible;
    deleteStartCityLineEdit->setVisible(isDeleteRoadInputVisible);
    deleteEndCityLineEdit->setVisible(isDeleteRoadInputVisible);
    confirmDeleteButton->setVisible(isDeleteRoadInputVisible);

    if (isDeleteRoadInputVisible) {
        deleteRoadButton->setText("Hide Delete Input");
        deleteStartCityLineEdit->clear();
        deleteEndCityLineEdit->clear();
    } else {
        deleteRoadButton->setText("Delete Road");
    }
}

void Options::onConfirmDeleteClicked()
{
    QString startCity = deleteStartCityLineEdit->text().trimmed();
    QString endCity = deleteEndCityLineEdit->text().trimmed();

    if (startCity.isEmpty() || endCity.isEmpty()) {
        QMessageBox::warning(this, "Error", "Both cities must be entered");
        return;
    }

    if (startCity == endCity) {
        QMessageBox::warning(this, "Error", "Start and end cities cannot be the same");
        return;
    }

    QString filePath = getUserGraphPath();
    if (filePath.isEmpty()) {
        QMessageBox::critical(this, "Error", "Cannot delete road - invalid map file path");
        return;
    }

    Graph graph;
    QVector<std::tuple<QString, QString, int>> edges = loadEdgesFromFile(filePath);
    graph.addGraphFromUI(edges);

    if (!graph.containsCity(startCity.toStdString())) {
        QMessageBox::warning(this, "Error", "Start city does not exist");
        return;
    }

    if (!graph.containsCity(endCity.toStdString())) {
        QMessageBox::warning(this, "Error", "End city does not exist");
        return;
    }

    if (!graph.deleteEdge(startCity.toStdString(), endCity.toStdString())) {
        QMessageBox::warning(this, "Error", "Failed to delete road (may not exist)");
        return;
    }

    updateFileAfterDeletion(startCity, endCity);
    QMessageBox::information(this, "Success", "Road deleted successfully");

    // Reset UI
    deleteStartCityLineEdit->clear();
    deleteEndCityLineEdit->clear();
    deleteStartCityLineEdit->setVisible(false);
    deleteEndCityLineEdit->setVisible(false);
    confirmDeleteButton->setVisible(false);
    deleteRoadButton->setText("Delete Road");
}

void Options::updateFileAfterDeletion(const QString& city1, const QString& city2)
{
    QString filePath = getUserGraphPath();
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open map file for reading");
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
        QMessageBox::critical(this, "Error", "Failed to open map file for writing");
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

    if (filePath.isEmpty()) {
        qDebug() << "Error: Empty file path";
        return edges;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath << "Error:" << file.errorString();
        return edges;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith("//")) continue;

        QStringList parts = line.split(',');
        if (parts.size() >= 2) {
            QString city1 = parts[0].trimmed();
            QString city2 = parts[1].trimmed();
            int distance = (parts.size() >= 3) ? parts[2].toInt() : 10;

            if (!city1.isEmpty() && !city2.isEmpty()) {
                edges.append(std::make_tuple(city1, city2, distance));
            }
        }
    }
    file.close();
    return edges;
}
