//
// Created by Mohamed Yassin on 01/05/2025.
//

#ifndef USER_H
#define USER_H
#include <string>
#include "Graph.h"
using namespace std;

class User {
private:
    string username;
    string password;
public:
    Graph graph;
    User();
    User(string, string);
    string getUsername();
    string getPassword();
    void setUsername(string);
    void setPassword(string);
};



#endif //USER_H
