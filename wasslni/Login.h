#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "Register.h"
#include "Map.h"
#include "Options.h"
#include <string>
#include <QString>
#include <QMessageBox>
#include <QDir>  

class QLineEdit;
class QLabel;

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

private slots:
    void onCreateAccountClicked();
    void showLogin();
    void onLoginClicked();
    void onUserLoggedOut();
    void onMapLoggedOut();
    void onAddNewMap();
    void showMapWindow();

private:
    string userEmail;
    QLineEdit *emailField;
    QLineEdit *passwordField;
    QLabel *createAccountButton;
    Register *registerWindow;
    Map *mapWindow;
    Options *optionsWindow;
};

#endif 
