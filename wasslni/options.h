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

private:
    QPushButton *showShortestPathButton;
    QPushButton *showPathButton;
    QLineEdit *startCityLineEdit;
    QLineEdit *endCityLineEdit;

    bool isPathInputVisible = false; // <-- مضاف لتتبع حالة الإظهار

    QVector<std::tuple<QString, QString, int>> loadEdgesFromFile(const QString& filePath);
};

#endif // OPTIONS_H
