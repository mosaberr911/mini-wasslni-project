#include "Login.h"
#include "FileManager.h"
#include "PathManager.h"
#include "UserManager.h"
#include <QApplication>
#include <QIcon>
#include <iostream>

int main(int argc, char *argv[])
{
    // SETTING PATH
    PathManager::setSystemPath("/Users/mohamed/CLionProjects/mini-wasslni-project/wasslni/");

    // CONSTANT FILE/IMAGE NAMES
    PathManager::setBackgroundFolderPath("images/Screenshot 2025-04-28 183435.png");
    PathManager::setUsersFilename("users.txt");
    PathManager::setGraphsFilename("graphs.txt");

    try {
        UserManager::loadUsersData();
    } catch (const exception& e) {
        qWarning() << "ERROR: Failed to read users data: " << e.what();
    }

    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/images/favicon.ico"));

    Login w;
    w.setWindowIcon(QIcon(":/images/favicon.ico"));  
    w.show();

    int result = a.exec();
    UserManager::saveUsersData();
    return result;
}
