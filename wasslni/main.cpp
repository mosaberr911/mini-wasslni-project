#include "login.h"
#include <QApplication>
#include <QIcon>  

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/images/favicon.ico"));

    Login w;
    w.setWindowIcon(QIcon(":/images/favicon.ico"));  
    w.show();

    return a.exec();
}
