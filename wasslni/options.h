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
    void onConfirmDeleteClicked(); // تمت إضافة هذا السلوط

private:
    QPushButton *showShortestPathButton;
    QPushButton *showPathButton;
    QPushButton *displayMapButton;
    QPushButton *addCityButton;
    QPushButton *saveCityButton;
    QPushButton *addRoadButton;
    QPushButton *saveRoadButton;
    QPushButton *deleteRoadButton;
    QPushButton *confirmDeleteButton; // تمت إضافة هذا الزر

    QLineEdit *startCityLineEdit;
    QLineEdit *endCityLineEdit;
    QLineEdit *addCityLineEdit;
    QLineEdit *roadStartCityLineEdit;
    QLineEdit *roadEndCityLineEdit;
    QLineEdit *roadDistanceLineEdit;
    QLineEdit *deleteStartCityLineEdit; // تمت إضافة هذا الحقل
    QLineEdit *deleteEndCityLineEdit;   // تمت إضافة هذا الحقل

    bool isPathInputVisible = false;
    bool isAddCityInputVisible = false;
    bool isAddRoadInputVisible = false;
    bool isDeleteRoadInputVisible = false; // تمت إضافة هذا المتغير

    QVector<std::tuple<QString, QString, int>> loadEdgesFromFile(const QString& filePath);
    void saveRoadToFile(const QString& city1, const QString& city2, int distance);
    void saveCityToFile(const QString& cityName);
    void updateFileAfterDeletion(const QString& city1, const QString& city2); // تمت إضافة هذه الدالة
};

#endif // OPTIONS_H
