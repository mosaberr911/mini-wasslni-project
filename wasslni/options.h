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
    void onShowShortestPathClicked();
    void onShowPathClicked();
    void onDisplayMapClicked();
    void onAddCityClicked();
    void onSaveCityClicked();
    void onAddRoadClicked();
    void onSaveRoadClicked();
    void onDeleteRoadClicked();
    void onConfirmDeleteClicked();
    void onDeleteCityClicked();
    void onConfirmDeleteCityClicked();

private:
    QPushButton *showShortestPathButton;
    QPushButton *showPathButton;
    QPushButton *displayMapButton;
    QPushButton *addCityButton;
    QPushButton *saveCityButton;
    QPushButton *addRoadButton;
    QPushButton *saveRoadButton;
    QPushButton *deleteRoadButton;
    QPushButton *confirmDeleteButton;
    QPushButton *deleteCityButton;
    QPushButton *confirmDeleteCityButton;

    QLineEdit *startCityLineEdit;
    QLineEdit *endCityLineEdit;
    QLineEdit *addCityLineEdit;
    QLineEdit *roadStartCityLineEdit;
    QLineEdit *roadEndCityLineEdit;
    QLineEdit *roadDistanceLineEdit;
    QLineEdit *deleteStartCityLineEdit;
    QLineEdit *deleteEndCityLineEdit;
    QLineEdit *deleteCityLineEdit;

    bool isPathInputVisible = false;
    bool isAddCityInputVisible = false;
    bool isAddRoadInputVisible = false;
    bool isDeleteRoadInputVisible = false;
    bool isDeleteCityInputVisible = false;

    QVector<std::tuple<QString, QString, int>> loadEdgesFromFile(const QString& filePath);
    void saveRoadToFile(const QString& city1, const QString& city2, int distance);
    void saveCityToFile(const QString& cityName);
    void updateFileAfterDeletion(const QString& city1, const QString& city2);
    void updateFileAfterCityDeletion(const QString& cityName);
};

#endif // OPTIONS_H
