#ifndef MAP_H
#define MAP_H

#include <QPushButton>
#include <QWidget>
#include <QLabel>
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

signals:
    void loggedOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onSubmitEdgeCount();
    void onSaveClicked();
    void onContinueClicked();
    void onAddMapClicked();
    void onOptionsLoggedOut();
    void onOptionsAddMap();

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
