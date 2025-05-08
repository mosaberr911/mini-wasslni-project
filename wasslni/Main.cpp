#include "Login.h"
#include <QApplication>
#include <QIcon>  // تأكد من إضافة هذه المكتبة

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // تعيين أيقونة التطبيق الرئيسية
    a.setWindowIcon(QIcon(":/images/favicon.ico"));

    Login w;
    w.setWindowIcon(QIcon(":/images/favicon.ico"));  // تعيين الأيقونة للنافذة
    w.show();

    return a.exec();
}
