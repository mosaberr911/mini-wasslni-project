//
// Created by Mohamed Yassin on 01/05/2025.
//

#ifndef USER_H
#define USER_H
#include <string>
#include "Graph.h"
using namespace std;
using AdjacencyList = unordered_map<string, vector<pair<string, float> > >;

class User {
private:
    string username;
    string password;
public:
    Graph graph;
    User();
    User(string, string);
    string getUsername() const;
    string getPassword() const;
    void setUsername(string);
    void setPassword(string);
};



#endif //USER_H
