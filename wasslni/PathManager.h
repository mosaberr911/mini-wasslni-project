#ifndef PATHMANAGER_H
#define PATHMANAGER_H
#include <string>
using namespace std;

class PathManager
{
private:
    static string systemPath;
    static string usersFilename;
    static string graphsFilename;
    static string backgroundFolderPath;
public:
    PathManager();

    static void setSystemPath(const string&);
    static string getSystemPath();

    static void setUsersFilename(const string&);
    static void setGraphsFilename(const string&);
    static void setBackgroundFolderPath(const string&);

    static string getUsersFilePath();
    static string getGraphsFilePath();
    static string getBackgroundImagePath();
};

#endif // PATHMANAGER_H
