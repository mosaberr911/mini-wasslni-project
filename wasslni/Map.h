#ifndef MAP_H
#define MAP_H

#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QVector>
#include <tuple>
#include "graph.h"
#include "Options.h"

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    void setUserEmail(const QString &email);

private slots:
    void onSubmitEdgeCount();
    void onSaveClicked();
    void onContinueClicked();
    void onAddMapClicked();

private:
    void saveGraphData(const QVector<std::tuple<QString, QString, int>> &edges);
    QString getUserGraphPath() const;

    QLineEdit *edgeCountField;
    QVBoxLayout *inputsLayout;
    QScrollArea *scrollArea;

    QPushButton *submitButton;
    QPushButton *saveButton;
    QPushButton *continueButton;
    QPushButton *addMapButton;

    QLabel *title;
    QLabel *nextPageLabel;

    struct EdgeInput {
        QLineEdit *cityA;
        QLineEdit *cityB;
        QLineEdit *distance;
    };

    QVector<EdgeInput> edgeInputs;
    Graph graph;
    QString userEmail;
    bool isSaved; // متغير جديد لتتبع حالة الحفظ
};

#endif // MAP_H
