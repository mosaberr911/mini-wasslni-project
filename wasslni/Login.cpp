#include "Login.h"
#include "UserManager.h"
#include "FileManager.h"
#include "PathManager.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDir>
#include <iostream>
#include "Map.h"
#include "Options.h"

Login::Login(QWidget *parent) : QWidget(parent), registerWindow(nullptr), mapWindow(nullptr)
{
    setFixedSize(600, 500);
    setWindowTitle("Wasslni - Login");

    QPixmap background(QString::fromStdString(PathManager::getBackgroundImagePath()));

    if (background.isNull()) {
        qDebug() << "Failed to load background image.";
        background = QPixmap(600, 500);
        background.fill(Qt::lightGray);
    }

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);

    QLabel *welcomeLabel = new QLabel("Welcome to Wasslni", this);
    welcomeLabel->setStyleSheet("font-size: 28px; color: #333; font-weight: bold;");
    welcomeLabel->setAlignment(Qt::AlignCenter);

    emailField = new QLineEdit(this);
    passwordField = new QLineEdit(this);
    passwordField->setEchoMode(QLineEdit::Password);

    QString textEditStyle = "QLineEdit {"
                            "background-color: white;"
                            "border: 2px solid #ddd;"
                            "border-radius: 8px;"
                            "padding: 8px 10px;"
                            "font-weight: bold;"
                            "color: #333;"
                            "font-size: 15px;"
                            "margin: 10px 0;"
                            "}";

    emailField->setStyleSheet(textEditStyle);
    passwordField->setStyleSheet(textEditStyle);

    emailField->setPlaceholderText("Enter your email");
    passwordField->setPlaceholderText("Enter your password");

    QPushButton *loginButton = new QPushButton("Login", this);
    loginButton->setStyleSheet("QPushButton {"
                               "background-color: #4CAF50;"
                               "min-height: 22px;"
                               "color: white;"
                               "border: none;"
                               "padding: 12px;"
                               "font-size: 16px;"
                               "border-radius: 8px;"
                               "font-weight: bold;"
                               "margin: 10px 0;}"
                               "QPushButton:hover {"
                               "background-color: #45a049;"
                               "}");

    createAccountButton = new QLabel("<center>Don't have an account? <a href='#' style='color: #0066cc; text-decoration: none; font-weight: bold;'>Create one</a></center>", this);
    createAccountButton->setStyleSheet("font-size: 16px; color: #555;");
    createAccountButton->setOpenExternalLinks(false);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addSpacing(40);
    layout->addWidget(welcomeLabel);
    layout->addSpacing(40);
    layout->addWidget(emailField);
    layout->addWidget(passwordField);
    layout->addSpacing(10);
    layout->addWidget(loginButton);
    layout->addSpacing(20);
    layout->addWidget(createAccountButton);
    layout->addSpacing(40);
    layout->setContentsMargins(80, 40, 80, 40);

    connect(createAccountButton, &QLabel::linkActivated, this, &Login::onCreateAccountClicked);
    connect(loginButton, &QPushButton::clicked, this, &Login::onLoginClicked);
}

void Login::onCreateAccountClicked()
{
    this->hide();
    if (!registerWindow) {
        registerWindow = new Register();
        connect(registerWindow, &Register::backToLoginRequested, this, &Login::showLogin);
    }
    registerWindow->show();
}

void Login::showLogin()
{
    this->show();
    // if (registerWindow) {
    //     registerWindow->hide();
    // }
    // if (optionsWindow) {
    //     optionsWindow->hide();
    // }
    // if (mapWindow) {
    //     mapWindow->hide();
    // }
    // Clear input fields for security
    emailField->clear();
    passwordField->clear();
}

void Login::onLoginClicked()
{
    try {
        QString email = emailField->text().trimmed();
        QString password = passwordField->text().trimmed();
        if (email.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill all fields!");
            return;
        }
        userEmail = email.toStdString();
        if (UserManager::checkUserCredentials(userEmail, password.toStdString())) {

            UserManager::loadUserGraph(PathManager::getGraphsFilePath(), userEmail);
            User user = UserManager::getUserByEmail(userEmail);

            if (!user.hasGraph()) {
                showMapWindow();
                this->hide();
            } else {
                optionsWindow = new Options();
                optionsWindow->setUserEmail(email.toStdString());
                connect(optionsWindow, &Options::loggedOut, this, &Login::onUserLoggedOut);
                connect(optionsWindow, &Options::addNewMap, this, &Login::onAddNewMap);
                optionsWindow->show();
                this->hide();
            }
            this->hide();
            QMessageBox::information(this, "Success", "Login successful!");
        } else {
            QMessageBox::warning(this, "Error", "Invalid email or password!");
        }
    } catch (const exception& e) {
        QMessageBox::critical(this, "Error", QString("Login failed: %1").arg(e.what()));
    }
}

void Login::showMapWindow() {
    if (!mapWindow) {
        mapWindow = new Map();
        connect(mapWindow, &Map::loggedOut, this, &Login::onMapLoggedOut);
        mapWindow->setUserEmail(userEmail);
    }
    mapWindow->show();
}

void Login::onUserLoggedOut()
{
    showLogin();
}

void Login::onMapLoggedOut()
{
    showLogin();
}

void Login::onAddNewMap() {
    showMapWindow();
}

Login::~Login() {
    if (registerWindow)
        delete registerWindow;
    if (mapWindow)
        delete mapWindow;
    if (optionsWindow)
        delete optionsWindow;
}
