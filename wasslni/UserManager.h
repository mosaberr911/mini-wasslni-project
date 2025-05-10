#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include "FileManager.h"
#include <unordered_map>
#include <string>
using namespace std;

class UserManager
{
private:
    static unordered_map<string, User> users;
public:
    UserManager();
    static void loadUsersData();
    static void saveUsersData();
    static bool checkUserCredentials(const string&, const string&);
    static bool containsUser(const string&);
    static User getUserByEmail(const string&);
    static void registerUser(const string&, const string&);
    static void updateUser(const User&);
    static void loadUserGraph(const string&, const string&);
    static void saveUserGraph(const string&, const string&);
    static void displayUsersData();
};

#endif // USERMANAGER_H
