#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

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

private:
    QPushButton *showShortestPathButton;
    QPushButton *showPathButton;
    QPushButton *displayMapButton; // إضافة زر Display Map
    QPushButton *addCityButton; // إضافة زر Add City
    QLineEdit *startCityLineEdit;
    QLineEdit *endCityLineEdit;
    QLineEdit *addCityLineEdit; // إضافة QLineEdit لمدينة جديدة

    bool isPathInputVisible = false;
    bool isAddCityInputVisible = false; // إضافة متغير لتتبع حالة إظهار صندوق نص المدينة

    QVector<std::tuple<QString, QString, int>> loadEdgesFromFile(const QString& filePath);
};

#endif // OPTIONS_H
