#include "Options.h"
#include "Graph.h"
#include "FileManager.h"
#include "PathManager.h"
#include "UserManager.h"
#include <QPushButton>
#include <QLineEdit>
#include <QInputDialog>
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

    QPixmap background(QString::fromStdString(PathManager::getBackgroundImagePath()));
    
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
    showPathButton->setStyleSheet("background-color: blue; color: white;");
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
    saveCityButton->setStyleSheet("background-color: blue; color: white;");
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
    confirmDeleteCityButton->setStyleSheet("background-color: red; color: white;");
    confirmDeleteCityButton->setFixedSize(elementWidth, elementHeight);
    confirmDeleteCityButton->setFont(font);
    confirmDeleteCityButton->setVisible(false);
    mainLayout->addWidget(confirmDeleteCityButton, 0, Qt::AlignHCenter);

    addRoadButton = new QPushButton("Add Road");
    addRoadButton->setStyleSheet("background-color: green; color: white;");
    addRoadButton->setFixedSize(elementWidth, elementHeight);
    addRoadButton->setFont(font);
    mainLayout->addWidget(addRoadButton, 0, Qt::AlignHCenter);

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
    saveRoadButton->setStyleSheet("background-color: blue; color: white;");
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
    confirmDeleteButton->setStyleSheet("background-color: red; color: white;");
    confirmDeleteButton->setFixedSize(elementWidth, elementHeight);
    confirmDeleteButton->setFont(font);
    confirmDeleteButton->setVisible(false);
    mainLayout->addWidget(confirmDeleteButton, 0, Qt::AlignHCenter);

    traverseMapButton = new QPushButton("Traverse Map");
    traverseMapButton->setStyleSheet("background-color: green; color: white;");
    traverseMapButton->setFixedSize(elementWidth, elementHeight);
    traverseMapButton->setFont(font);
    mainLayout->addWidget(traverseMapButton, 0, Qt::AlignHCenter);

    // Create a horizontal layout for DFS and BFS buttons
    QHBoxLayout *traverseButtonsLayout = new QHBoxLayout();
    traverseButtonsLayout->setSpacing(10);

    dfsButton = new QPushButton("Using DFS");
    dfsButton->setStyleSheet("background-color: #4CAF50; color: white;");
    dfsButton->setFixedSize(elementWidth/2 - 5, elementHeight);
    dfsButton->setFont(font);
    dfsButton->setVisible(false);
    traverseButtonsLayout->addWidget(dfsButton);

    bfsButton = new QPushButton("Using BFS");
    bfsButton->setStyleSheet("background-color: #4CAF50; color: white;");
    bfsButton->setFixedSize(elementWidth/2 - 5, elementHeight);
    bfsButton->setFont(font);
    bfsButton->setVisible(false);
    traverseButtonsLayout->addWidget(bfsButton);

    mainLayout->addLayout(traverseButtonsLayout);

    isTraverseInputVisible = false;
    isPathInputVisible = false;
    isAddCityInputVisible = false;
    isDeleteCityInputVisible = false;
    isAddRoadInputVisible = false;
    isDeleteRoadInputVisible = false;

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
    connect(traverseMapButton, &QPushButton::clicked, this, &Options::onTraverseMapClicked);
    connect(dfsButton, &QPushButton::clicked, this, &Options::onDFSClicked);
    connect(bfsButton, &QPushButton::clicked, this, &Options::onBFSClicked);
}

void Options::setUserEmail(const string &userEmail) {
    this->userEmail = userEmail;
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
    try {
        QString startCity = startCityLineEdit->text().trimmed();
        QString endCity = endCityLineEdit->text().trimmed();

        if (startCity.isEmpty() || endCity.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Both cities must be entered!");
            return;
        }

        User user = UserManager::getUserByEmail(userEmail);
        std::string result = user.showShortestPath(startCity.toStdString(), endCity.toStdString());
        QMessageBox::information(this, "Shortest Path", QString::fromStdString(result));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to show shortest path: %1").arg(e.what()));
    }
}

void Options::onDisplayMapClicked()
{
    try {
        User user = UserManager::getUserByEmail(userEmail);
        QString mapContent = QString::fromStdString(user.displayMap());

        QDialog dialog(this);
        dialog.setWindowTitle("Map Viewer - " + QString::fromStdString(user.getEmail()));
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

void Options::onSaveCityClicked() {
    try {
        QString cityName = addCityLineEdit->text().trimmed();
        if (cityName.isEmpty()) {
            QMessageBox::warning(this, "Error", "City name cannot be empty");
            return;
        }
        User user = UserManager::getUserByEmail(userEmail);
        user.addCity(cityName.toStdString());

        UserManager::updateUser(user);
        UserManager::saveUserGraph(userEmail, PathManager::getGraphsFilePath());

        QMessageBox::information(this, "Success", "City added successfully");

        addCityLineEdit->clear();
        addCityLineEdit->setVisible(false);
        saveCityButton->setVisible(false);
        addCityButton->setText("Add City");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to add city: %1").arg(e.what()));
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
    try {
        QString cityName = deleteCityLineEdit->text().trimmed();
        if (cityName.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter a city name");
            return;
        }

        User user = UserManager::getUserByEmail(userEmail);
        user.deleteCity(cityName.toStdString());

        UserManager::updateUser(user);
        UserManager::saveUserGraph(userEmail, PathManager::getGraphsFilePath());


        QMessageBox::information(this, "Success", "City deleted successfully");
        // Reset UI
        deleteCityLineEdit->clear();
        deleteCityLineEdit->setVisible(false);
        confirmDeleteCityButton->setVisible(false);
        deleteCityButton->setText("Delete City");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to delete city: %1").arg(e.what()));
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
        roadStartCityLineEdit->clear();
        roadEndCityLineEdit->clear();
        roadDistanceLineEdit->clear();
    } else {
        addRoadButton->setText("Add Road");
    }
}

void Options::onSaveRoadClicked()
{
    try {
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

        User user = UserManager::getUserByEmail(userEmail);
        user.addRoad(startCity.toStdString(), endCity.toStdString(), distanceStr.toFloat());

        UserManager::updateUser(user);
        UserManager::saveUserGraph(userEmail, PathManager::getGraphsFilePath());


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
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to add road: %1").arg(e.what()));
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
        deleteStartCityLineEdit->clear();
        deleteEndCityLineEdit->clear();
    } else {
        deleteRoadButton->setText("Delete Road");
    }
}

void Options::onConfirmDeleteClicked()
{
    try {
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

        User user = UserManager::getUserByEmail(userEmail);
        user.deleteRoad(startCity.toStdString(), endCity.toStdString());

        UserManager::updateUser(user);
        UserManager::saveUserGraph(userEmail, PathManager::getGraphsFilePath());

        QMessageBox::information(this, "Success", "Road deleted successfully");

        // Reset UI
        deleteStartCityLineEdit->clear();
        deleteEndCityLineEdit->clear();
        deleteStartCityLineEdit->setVisible(false);
        deleteEndCityLineEdit->setVisible(false);
        confirmDeleteButton->setVisible(false);
        deleteRoadButton->setText("Delete Road");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to delete road: %1").arg(e.what()));
    }
}

void Options::onTraverseMapClicked()
{
    isTraverseInputVisible = !isTraverseInputVisible;

    dfsButton->setVisible(isTraverseInputVisible);
    bfsButton->setVisible(isTraverseInputVisible);

    if (isTraverseInputVisible) {
        traverseMapButton->setText("Hide Traverse Options");
    } else {
        traverseMapButton->setText("Traverse Map");
    }
}

void Options::onDFSClicked()
{
    try {
        bool ok;
        QString startNode = QInputDialog::getText(this, "DFS Start Node", "Enter the starting node:", QLineEdit::Normal, "", &ok);
        if (!ok || startNode.isEmpty()) {
            QMessageBox::critical(this, "Error", "Invalid start node");
            return;
        }

        QTextEdit* output = new QTextEdit(this);
        output->setReadOnly(true);

        User user = UserManager::getUserByEmail(userEmail);
        user.displayDfs(startNode, output);

        QMessageBox::information(this, "DFS Traversal", output->toPlainText());
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to traverse using DFS algorithm: %1").arg(e.what()));
    }
}

void Options::onBFSClicked()
{
    try {
        bool ok;
        QString startNode = QInputDialog::getText(this, "BFS Start Node", "Enter the starting node:", QLineEdit::Normal, "", &ok);
        if (!ok || startNode.isEmpty()) {
            QMessageBox::critical(this, "Error", "Invalid start node");
            return;
        }

        QTextEdit* output = new QTextEdit(this);
        output->setReadOnly(true);

        User user = UserManager::getUserByEmail(userEmail);
        user.displayBfs(startNode, output);

        QMessageBox::information(this, "BFS Traversal", output->toPlainText());
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to travers using BFS algorithm: %1").arg(e.what()));
    }
}
