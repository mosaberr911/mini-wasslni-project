#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "register.h"  // إضافة هيدر الريجستر
#include "Map.h"      // إضافة هيدر صفحة الماب
#include <QString>      // لإضافة QString
#include <QMessageBox>  // لعرض رسائل التنبيه في حالة الخطأ

class QLineEdit;
class QLabel;

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

private slots:
    void onCreateAccountClicked();  // عند النقر على رابط إنشاء حساب جديد
    void showLogin();              // دالة لعرض صفحة تسجيل الدخول
    void onLoginClicked();         // دالة جديدة للتحقق من بيانات الدخول

private:
    bool checkCredentials(const QString &email, const QString &password); // دالة التحقق من البيانات

    QLineEdit *emailField;
    QLineEdit *passwordField;
    QLabel *createAccountButton;
    Register *registerWindow;  // مؤشر لنافذة التسجيل
    Map *mapWindow;            // مؤشر لنافذة الماب
};

#endif // LOGIN_H
