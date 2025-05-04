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
    void onDisplayMapClicked(); // إضافة التابع الخاص بـ Display Map
    void onAddCityClicked(); // إضافة التابع الخاص بـ Add City
    void onSaveCityClicked(); // إضافة التابع الخاص بـ Save City
    void onAddRoadClicked(); // إضافة التابع الخاص بـ Add Road
    void onSaveRoadClicked(); // إضافة التابع الخاص بـ Save Road

private:
    QPushButton *showShortestPathButton;
    QPushButton *showPathButton;
    QPushButton *displayMapButton; // إضافة زر Display Map
    QPushButton *addCityButton; // إضافة زر Add City
    QPushButton *saveCityButton; // إضافة زر Save City
    QPushButton *addRoadButton; // إضافة زر Add Road
    QPushButton *saveRoadButton; // إضافة زر Save Road

    QLineEdit *startCityLineEdit;
    QLineEdit *endCityLineEdit;
    QLineEdit *addCityLineEdit; // إضافة QLineEdit لمدينة جديدة
    QLineEdit *roadStartCityLineEdit; // إضافة QLineEdit لبداية الطريق
    QLineEdit *roadEndCityLineEdit; // إضافة QLineEdit لنهاية الطريق
    QLineEdit *roadDistanceLineEdit; // إضافة QLineEdit للمسافة

    bool isPathInputVisible = false;
    bool isAddCityInputVisible = false; // إضافة متغير لتتبع حالة إظهار صندوق نص المدينة
    bool isAddRoadInputVisible = false; // إضافة متغير لتتبع حالة إظهار حقول الطريق

    QVector<std::tuple<QString, QString, int>> loadEdgesFromFile(const QString& filePath);

    void saveRoadToFile(const QString& city1, const QString& city2, int distance);
    void saveCityToFile(const QString& cityName); // دالة لحفظ المدينة في الملف
};

#endif // OPTIONS_H
