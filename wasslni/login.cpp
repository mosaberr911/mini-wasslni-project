#include "Login.h"
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
#include "Map.h"

Login::Login(QWidget *parent) : QWidget(parent), registerWindow(nullptr), mapWindow(nullptr)
{
    setFixedSize(600, 500);
    setWindowTitle("Wasslni - Login");

    // إعداد الخلفية من صورة
    QPixmap background("C:/Users/A/OneDrive/Documents/wasslni/images/Screenshot 2025-04-28 183435.png");
    if (background.isNull()) {
        qDebug() << "Failed to load background image.";
        background = QPixmap(600, 500);
        background.fill(Qt::lightGray);
    }

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);

    // إعداد عنوان الترحيب
    QLabel *welcomeLabel = new QLabel("Welcome to Wasslni", this);
    welcomeLabel->setStyleSheet("font-size: 28px; color: #333; font-weight: bold;");
    welcomeLabel->setAlignment(Qt::AlignCenter);

    // إنشاء حقول الإدخال
    emailField = new QLineEdit(this);
    passwordField = new QLineEdit(this);
    passwordField->setEchoMode(QLineEdit::Password);

    // تنسيق الحقول
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

    // إعداد زر الدخول
    QPushButton *loginButton = new QPushButton("Login", this);
    loginButton->setStyleSheet("QPushButton {"
                               "background-color: #4CAF50;"
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

    // نص "Don't have an account" مع رابط
    createAccountButton = new QLabel("<center>Don't have an account? <a href='#' style='color: #0066cc; text-decoration: none; font-weight: bold;'>Create one</a></center>", this);
    createAccountButton->setStyleSheet("font-size: 16px; color: #555;");
    createAccountButton->setOpenExternalLinks(false);

    // التخطيط
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

    // ربط الأحداث
    connect(createAccountButton, &QLabel::linkActivated, this, &Login::onCreateAccountClicked);
    connect(loginButton, &QPushButton::clicked, this, &Login::onLoginClicked);
}

void Login::onCreateAccountClicked()
{
    this->hide();  // إخفاء نافذة اللوجين
    if (!registerWindow) {
        registerWindow = new Register();
        connect(registerWindow, &Register::backToLoginRequested, this, &Login::showLogin);
    }
    registerWindow->show();
}

void Login::showLogin()
{
    this->show();
    if (registerWindow) {
        registerWindow->hide();
    }
}

bool Login::checkCredentials(const QString &email, const QString &password)
{
    // فتح ملف المستخدم
    QString filePath = "C:/Users/A/OneDrive/Documents/wasslni/users.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open user data file.");
        return false;
    }

    QTextStream in(&file);
    bool found = false;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList data = line.split(',');

        if (data.size() == 2) {
            QString emailFromFile = data[0].trimmed();
            QString passwordFromFile = data[1].trimmed();

            if (emailFromFile == email && passwordFromFile == password) {
                found = true;
                break;
            }
        }
    }

    file.close();
    return found;
}

void Login::onLoginClicked()
{
    QString email = emailField->text().trimmed();
    QString password = passwordField->text().trimmed();

    if (checkCredentials(email, password)) {
        createUserMapFile(email);

        QMessageBox::information(this, "Success", "Login successful!");

        this->hide();
        if (!mapWindow) {
            mapWindow = new Map();
            mapWindow->setUserEmail(email);  // تأكد من وجود هذا السطر
        }
        mapWindow->show();
    } else {
        QMessageBox::warning(this, "Error", "Incorrect email or password.");
    }
}
void Login::createUserMapFile(const QString &email)
{
    // Create maps directory if it doesn't exist
    QDir dir("C:/Users/A/OneDrive/Documents/wasslni/maps");
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            QMessageBox::warning(this, "Error", "Could not create maps directory.");
            return;
        }
    }

    // Sanitize email to create filename (replace special characters)
    QString sanitizedEmail = email;
    sanitizedEmail.replace("@", "_at_");
    sanitizedEmail.replace(".", "_dot_");
    sanitizedEmail.replace(QRegularExpression("[^a-zA-Z0-9_]"), "_");  // Updated for Qt 6

    // Create file path
    QString filePath = QString("C:/Users/A/OneDrive/Documents/wasslni/maps/%1_map.txt").arg(sanitizedEmail);

    // Check if file already exists
    if (QFile::exists(filePath)) {
        qDebug() << "User map file already exists:" << filePath;
        return;
    }

    // Create new file
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "// User map file for: " << email << "\n";
        out << "// Created on: " << QDateTime::currentDateTime().toString() << "\n";
        out << "// Add your map data here\n";
        file.close();
        qDebug() << "Created user map file:" << filePath;
    } else {
        QMessageBox::warning(this, "Error", "Could not create user map file.");
    }
}
