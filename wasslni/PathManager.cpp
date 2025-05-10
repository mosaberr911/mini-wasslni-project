#include "PathManager.h"

PathManager::PathManager() = default;

string PathManager::systemPath;
string PathManager::usersFilename;
string PathManager::graphsFilename;
string PathManager::backgroundFolderPath;

void PathManager::setSystemPath(const string &path) {
    systemPath = path;
}

string PathManager::getSystemPath() {
    return systemPath;
}

void PathManager::setUsersFilename(const string &filename) {
    usersFilename = filename;
}

string PathManager::getUsersFilePath() {
    return systemPath + usersFilename;
}

void PathManager::setGraphsFilename(const string &filename) {
    graphsFilename = filename;
}

string PathManager::getGraphsFilePath() {
    return systemPath + graphsFilename;
}

void PathManager::setBackgroundFolderPath(const string &folderPath) {
    backgroundFolderPath = folderPath;
}

string PathManager::getBackgroundImagePath() {
    return systemPath + backgroundFolderPath;
}
