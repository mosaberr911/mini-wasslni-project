#include "Register.h"
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

    // إعداد الخلفية من نفس الصورة
    QPixmap background("C:/Users/A/OneDrive/Documents/wasslni/images/Screenshot 2025-04-28 183435.png");
    if (background.isNull()) {
        qDebug() << "Failed to load background image in Register.";
        background = QPixmap(600, 500);
        background.fill(Qt::lightGray);
    }

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);

    // العنوان الرئيسي
    QLabel *titleLabel = new QLabel("Create Account", this);
    titleLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: black;");
    titleLabel->setAlignment(Qt::AlignCenter);

    // حقول الإدخال
    nameField = new QLineEdit(this);
    emailField = new QLineEdit(this);
    passwordField = new QLineEdit(this);
    passwordField->setEchoMode(QLineEdit::Password);
    confirmPasswordField = new QLineEdit(this);
    confirmPasswordField->setEchoMode(QLineEdit::Password);

    // تنسيق الحقول
    QString fieldStyle = "QLineEdit {"
                         "background: white;"
                         "border: 1px solid #ccc;"
                         "border-radius: 5px;"
                         "padding: 10px;"
                         "font-weight: bold;"
                         "color: black;"
                         "font-size: 14px;" // تم تقليص حجم النص هنا
                         "margin: 5px;"
                         "}";

    nameField->setStyleSheet(fieldStyle);
    emailField->setStyleSheet(fieldStyle);
    passwordField->setStyleSheet(fieldStyle);
    confirmPasswordField->setStyleSheet(fieldStyle);

    nameField->setPlaceholderText("Full Name");
    emailField->setPlaceholderText("Email");
    passwordField->setPlaceholderText("Password");
    confirmPasswordField->setPlaceholderText("Confirm Password");

    // الأزرار
    registerButton = new QPushButton("Register", this);
    backButton = new QPushButton("Back to Login", this);

    // تنسيق الأزرار
    QString buttonStyle = "QPushButton {"
                          "background-color: #4CAF50;"
                          "color: white;"
                          "border: none;"
                          "padding: 10px;"
                          "font-size: 16px;"
                          "border-radius: 5px;"
                          "margin: 5px;"
                          "} "
                          "QPushButton:hover {"
                          "background-color: #45a049;"
                          "}";

    registerButton->setStyleSheet(buttonStyle);
    backButton->setStyleSheet(buttonStyle.replace("#4CAF50", "#f44336").replace("#45a049", "#d32f2f"));

    // التخطيط
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addSpacing(20);
    layout->addWidget(nameField);
    layout->addWidget(emailField);
    layout->addWidget(passwordField);
    layout->addWidget(confirmPasswordField);
    layout->addSpacing(20);
    layout->addWidget(registerButton);
    layout->addWidget(backButton);
    layout->setContentsMargins(50, 50, 50, 50);

    // توصيل الإشارات
    connect(registerButton, &QPushButton::clicked, this, &Register::onRegisterClicked);
    connect(backButton, &QPushButton::clicked, this, &Register::onBackClicked);
}

void Register::onRegisterClicked()
{
    // التحقق من صحة البيانات
    if (passwordField->text() != confirmPasswordField->text()) {
        QMessageBox::warning(this, "Error", "Passwords do not match!");
        return;
    }

    // مسار الملف الذي سيتم تخزين البيانات فيه
    QString filePath = "C:/Users/A/OneDrive/Documents/wasslni/users.txt";

    // فتح الملف في وضع الكتابة
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open file for writing.");
        return;
    }

    // كتابة البيانات في الملف بصيغة "البريد الإلكتروني,كلمة المرور"
    QTextStream out(&file);
    out << emailField->text() << "," << passwordField->text() << "\n";

    file.close();

    // إشعار المستخدم بنجاح التسجيل
    QMessageBox::information(this, "Success", "Account created successfully!");

    // العودة إلى صفحة تسجيل الدخول
    emit backToLoginRequested();
}

void Register::onBackClicked()
{
    emit backToLoginRequested();
}
