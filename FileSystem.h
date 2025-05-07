//
// Created by Mohamed Yassin on 04/05/2025.
//

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <vector>
#include <unordered_map>
#include <string>
#include "User.h"

using namespace std;
using AdjacencyList = unordered_map<string, vector<pair<string, float> > >;

class FileSystem {

public:
    FileSystem();
    static vector<string> convertAdjListToGraphLines(AdjacencyList adj);
    static AdjacencyList parseGraphLines(const vector<string>& graphLines);
    static void saveGraphToFile(const string& filename, User& targetUser);
    static void loadGraphFromFile(const string& filename, User& targetUser);
    static void deleteUserGraph(const string& filename, User& targetUser);
    static void saveUsers(const string& filename, const unordered_map<string, User> users);
    static unordered_map<string, User> loadUsers(const string& filename);
};



#endif //FILESYSTEM_H
