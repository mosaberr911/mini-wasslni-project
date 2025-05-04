#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVector>
#include <tuple>

class Options : public QWidget
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);

private slots:
    // Slot functions for button clicks
    void onShowShortestPathClicked();
    void onShowPathClicked();
    void onDisplayMapClicked(); // Slot for displaying the map
    void onAddCityClicked();   // Slot for adding a new city
    void onSaveCityClicked();  // Slot for saving the new city
    void onAddRoadClicked();   // Slot for adding a road
    void onSaveRoadClicked();  // Slot for saving the new road
    void onDeleteRoadClicked(); // Slot for deleting a road
    void onConfirmDeleteClicked(); // Slot for confirming road deletion

private:
    // Buttons for various actions
    QPushButton *showShortestPathButton;
    QPushButton *showPathButton;
    QPushButton *displayMapButton; // Button for displaying the map
    QPushButton *addCityButton;    // Button for adding a new city
    QPushButton *saveCityButton;   // Button for saving the city
    QPushButton *addRoadButton;    // Button for adding a new road
    QPushButton *saveRoadButton;   // Button for saving the road
    QPushButton *deleteRoadButton; // Button for deleting a road
    QPushButton *confirmDeleteButton; // Button for confirming road deletion

    // Line edit widgets for user input
    QLineEdit *startCityLineEdit;    // Line edit for start city
    QLineEdit *endCityLineEdit;      // Line edit for end city
    QLineEdit *addCityLineEdit;      // Line edit for adding a new city
    QLineEdit *roadStartCityLineEdit; // Line edit for road start city
    QLineEdit *roadEndCityLineEdit;   // Line edit for road end city
    QLineEdit *roadDistanceLineEdit;  // Line edit for road distance
    QLineEdit *deleteStartCityLineEdit; // Line edit for deleting road start city
    QLineEdit *deleteEndCityLineEdit;   // Line edit for deleting road end city

    // Booleans to track visibility of input fields
    bool isPathInputVisible = false;
    bool isAddCityInputVisible = false; // Tracks visibility of add city input
    bool isAddRoadInputVisible = false; // Tracks visibility of add road input
    bool isDeleteRoadInputVisible = false; // Tracks visibility of delete road input

    // Helper functions
    QVector<std::tuple<QString, QString, int>> loadEdgesFromFile(const QString& filePath);
    void saveRoadToFile(const QString& city1, const QString& city2, int distance);
    void saveCityToFile(const QString& cityName); // Function to save city to file
    void updateFileAfterDeletion(const QString& city1, const QString& city2); // Function to update file after road deletion
};

#endif // OPTIONS_H
