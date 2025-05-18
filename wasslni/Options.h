#ifndef OPTIONS_H
#define OPTIONS_H

#include "User.h"
#include "GraphVisualizer.h"
#include <QWidget>
#include <QVector>
#include <tuple>

class QPushButton;
class QLineEdit;
class QLabel;
class Graph;

class Options : public QWidget
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);
    void setUserEmail(const string &email);
    QString getUserEmail() const;

signals:
    void loggedOut(); // Signal emitted when user logs out
    void addNewMap();

private slots:
    void onTraverseMapClicked();
    void onDFSClicked();
    void onBFSClicked();
    void onShowShortestPathClicked();
    void onShowPathClicked();
    void onDisplayMapClicked();
    void onAddCityClicked();
    void onSaveCityClicked();
    void onDeleteCityClicked();
    void onConfirmDeleteCityClicked();
    void onAddRoadClicked();
    void onSaveRoadClicked();
    void onDeleteRoadClicked();
    void onConfirmDeleteClicked();
    void onLogOutClicked();
    void onAddNewMapClicked();
    void onVisualizeGraphClicked();
    void onVisualizerReturn();
    void onShowMinimumSpanningTreeClicked();

private:
    QPushButton* traverseMapButton;
    QPushButton* dfsButton;
    QPushButton* bfsButton;
    QPushButton* logOutButton;
    QPushButton* addNewMapButton;
    QPushButton* visualizeGraphButton;
    QPushButton* showMinimumSpanningTreeButton;
    bool isTraverseInputVisible;

    string userEmail;
    bool isAddCityInputVisible = false;
    bool isDeleteCityInputVisible = false;
    bool isAddRoadInputVisible = false;
    bool isDeleteRoadInputVisible = false;
    bool isPathInputVisible = false;

    GraphVisualizer* visualizer;

    QPushButton *showShortestPathButton;
    QLineEdit *startCityLineEdit;
    QLineEdit *endCityLineEdit;
    QPushButton *showPathButton;
    QPushButton *displayMapButton;
    QPushButton *addCityButton;
    QLineEdit *addCityLineEdit;
    QPushButton *saveCityButton;
    QPushButton *deleteCityButton;
    QLineEdit *deleteCityLineEdit;
    QPushButton *confirmDeleteCityButton;
    QPushButton *addRoadButton;
    QLineEdit *roadStartCityLineEdit;
    QLineEdit *roadEndCityLineEdit;
    QLineEdit *roadDistanceLineEdit;
    QPushButton *saveRoadButton;
    QPushButton *deleteRoadButton;
    QLineEdit *deleteStartCityLineEdit;
    QLineEdit *deleteEndCityLineEdit;
    QPushButton *confirmDeleteButton;
};

#endif 
