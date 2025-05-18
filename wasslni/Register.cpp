#include "Register.h"
#include "UserManager.h"
#include "PathManager.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QPalette>
#include <QFile>
#include <QTextStream>

Register::Register(QWidget *parent) : QWidget(parent)
{
    setFixedSize(600, 500);
    setWindowTitle("Create New Account");

    QPixmap background(QString::fromStdString(PathManager::getBackgroundImagePath()));
    
    if (background.isNull()) {
        qDebug() << "Failed to load background image in Register.";
        background = QPixmap(600, 500);
        background.fill(Qt::lightGray);
    }

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);

    QLabel *titleLabel = new QLabel("Create Account", this);
    titleLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: black;");
    titleLabel->setAlignment(Qt::AlignCenter);

    nameField = new QLineEdit(this);
    emailField = new QLineEdit(this);
    passwordField = new QLineEdit(this);
    passwordField->setEchoMode(QLineEdit::Password);
    confirmPasswordField = new QLineEdit(this);
    confirmPasswordField->setEchoMode(QLineEdit::Password);

    QString fieldStyle = "QLineEdit {"
                         "min-width: 100px;"
                         "min-height: 22px;"
                         "background: white;"
                         "border: 1px solid #ccc;"
                         "border-radius: 5px;"
                         "padding: 10px;"
                         "font-weight: bold;"
                         "color: black;"
                         "font-size: 14px;"
                         "margin: 5px;"
                         "font-family: Arial;"
                         "}";

    nameField->setStyleSheet(fieldStyle);
    emailField->setStyleSheet(fieldStyle);
    passwordField->setStyleSheet(fieldStyle);
    confirmPasswordField->setStyleSheet(fieldStyle);

    nameField->setPlaceholderText("Full Name");
    emailField->setPlaceholderText("Email");
    passwordField->setPlaceholderText("Password");
    confirmPasswordField->setPlaceholderText("Confirm Password");

    nameField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    emailField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    passwordField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    confirmPasswordField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    registerButton = new QPushButton("Register", this);
    backButton = new QPushButton("Back to Login", this);

    QString buttonStyle = "QPushButton {"
                          "background-color: #4CAF50;"
                          "min-height: 22px;"
                          "color: white;"
                          "border: none;"
                          "padding: 10px;"
                          "font-size: 16px;"
                          "border-radius: 5px;"
                          "margin: 5px;"
                          "min-width: 150px;"
                          "} "
                          "QPushButton:hover {"
                          "background-color: #45a049;"
                          "}";

    registerButton->setStyleSheet(buttonStyle);
    backButton->setStyleSheet(buttonStyle.replace("#4CAF50", "#2196F3").replace("#45a049", "#0b7dda"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addSpacing(30);
    layout->addWidget(nameField);
    layout->addSpacing(10);
    layout->addWidget(emailField);
    layout->addSpacing(10);
    layout->addWidget(passwordField);
    layout->addSpacing(10);
    layout->addWidget(confirmPasswordField);
    layout->addSpacing(30);
    layout->addWidget(registerButton);
    layout->addWidget(backButton);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setAlignment(Qt::AlignCenter);

    connect(registerButton, &QPushButton::clicked, this, &Register::onRegisterClicked);
    connect(backButton, &QPushButton::clicked, this, &Register::onBackClicked);
}

void Register::onRegisterClicked()
{
    try {
        QString email = emailField->text().trimmed();
        QString password = passwordField->text();

        if (passwordField->text() != confirmPasswordField->text()) {
            QMessageBox::warning(this, "Error", "Passwords do not match!");
            return;
        }

        if (UserManager::containsUser(email.toStdString())) {
            QMessageBox::warning(this, "Error", "Email already exists!");
            return;
        }

        UserManager::registerUser(email.toStdString(), password.toStdString());

        // immediately save users data: prevent data loss
        UserManager::saveUsersData();

        QMessageBox::information(this, "Success", "Account created successfully!");

        emit backToLoginRequested();
        this->close();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to register user: %1").arg(e.what()));
    }
}

void Register::onBackClicked()
{
    emit backToLoginRequested();
    this->close();
}
