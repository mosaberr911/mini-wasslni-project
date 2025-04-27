#include<iostream>
#include<vector>
#include<map>
#include <unordered_map>
#include<set>
#include<string>
using namespace std;
struct User {
    string password;
    string role;
};

class ConsoleApp {
private:
    unordered_map<string, User> users;
public:
    ConsoleApp();
    void signUp();
    void login();
    void saveUsers() const;
    void loadUsers();
    void adminMenu();
    void userMenu();
};