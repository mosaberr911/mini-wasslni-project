#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);

signals:
    void backToLoginRequested();  
private slots:
    void onRegisterClicked();
    void onBackClicked();

private:
    QLineEdit *nameField;
    QLineEdit *emailField;
    QLineEdit *passwordField;
    QLineEdit *confirmPasswordField;
    QPushButton *registerButton;
    QPushButton *backButton;
};

#endif 
