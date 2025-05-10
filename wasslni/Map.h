#ifndef MAP_H
#define MAP_H

#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QVector>
#include <tuple>
#include "Graph.h"
#include "Options.h"

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    void setUserEmail(const string& userEmail);

private slots:
    void onSubmitEdgeCount();
    void onSaveClicked();
    void onContinueClicked();
    void onAddMapClicked();

private:

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
    string userEmail;
    bool isSaved;
};

#endif 
