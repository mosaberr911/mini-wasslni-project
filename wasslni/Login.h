#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "register.h"
#include "Map.h"
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

private:
    bool checkCredentials(const QString &email, const QString &password);
    void createUserMapFile(const QString &email);  

    QLineEdit *emailField;
    QLineEdit *passwordField;
    QLabel *createAccountButton;
    Register *registerWindow;
    Map *mapWindow;
};

#endif 
