#include<iostream>
#include<vector>
#include<map>
#include <unordered_map>
#include<set>
#include<string>
#include "User.h"
using namespace std;

class ConsoleApp {
private:
    unordered_map<string, User> users;
public:
    ConsoleApp();
    void signUp();
    void login();
    void saveUsers() const;
    void loadUsers();
    void userMenu(User&);
    static void displayUserMenuOptions();
    static int getValidatedMenuChoice(int min, int max);
    static void executeUserMenuAction(int choice, User& thisUser);
    void mainMenu();
};