#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <unordered_map>
#include <string>
#include "User.h"

using namespace std;
using AdjacencyList = unordered_map<string, vector<pair<string, float> > >;

class FileManager
{
public:
    FileManager();
    static void saveGraphToFile(const string& filename, User& targetUser);
    static void loadGraphFromFile(const string& filename, const string& email);
    static void deleteUserGraph(const string& filename, User& targetUser);
    static void saveUsers(const string& filename, const unordered_map<string, User>& users);
    static unordered_map<string, User> loadUsers(const string& filename);
    static bool fileExists(const string& path);
};

#endif // FILEMANAGER_H
