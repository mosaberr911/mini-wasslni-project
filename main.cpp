#include <iostream>
#include "Graph.h"
#include "bits/stdc++.h"
int main() {
    Graph graph ;
    graph.addGraph();
    graph.displayGraph();

    // files hadling / exception handling / qt files  /
    // saber qt,code  :: gamil qt :: kyrollos files :: yaseen testing\exception handle  :: ashraf , sherif console app


    return 0;
}






/*
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;
struct User {
    string password;
    string role;
};

unordered_map<string, User> loadUsers() {
    unordered_map<string, User> users;
    ifstream file("users.txt");
    if (file.is_open()) {
        string username, password, role;
        while (file >> username >> password >> role) {
            users[username] = { password, role };
        }
        file.close();
    }
    return users;
}

void saveUsers(const unordered_map<string, User>& users) {
    ofstream file("users.txt");
    for (const auto& pair : users) {
        file << pair.first << " " << pair.second.password << " " << pair.second.role << endl;
    }
    file.close();
}

void signUp(unordered_map<string, User>& users) {
    string username, password, role;
    cout << "Enter your username: ";
    cin >> ws;
    getline(cin, username);

    if (users.find(username) != users.end()) {
        cout << "Username already exists!\n";
        return;
    }

    cout << "Enter your password: ";
    getline(cin, password);

    cout << "Are you an Admin or User? (admin/user): ";
    getline(cin, role);

    if (role != "admin" && role != "user") {
        cout << "Invalid role. Please choose 'admin' or 'user'.\n";
        return;
    }

    users[username] = { password, role };
    saveUsers(users);
    cout << "Account created successfully for " << username << " as " << role << ".\n";
}

void login(unordered_map<string, User>& users) {
    string username, password;

    cout << "Enter your username: ";
    cin >> ws;          //to clear spaces
    getline(cin, username);

    if (users.find(username) == users.end()) {
        cout << "Username not found.\n";
        return;
    }

    cout << "Enter your password: ";
    getline(cin, password);

    if (password == users[username].password) {
        cout << "Welcome " << username << "!\n";
        if (users[username].role == "admin") {
            cout << "Accessing Admin Functions...\n"; //tell you put the Functions
        }
        else {
            cout << "Accessing User Functions...\n"; //tell you put the functions
        }
    }
    else {
        cout << "Incorrect password.\n";
        string forgot;
        cout << "Forgot your password? (yes/no): ";
        cin >> forgot;
        if (forgot == "yes") {
            cout << "Reset Password Function (Placeholder)\n"; //for reset pass if we need it
        }
    }
}

int main() {
    unordered_map<string, User> users = loadUsers();
    int choice;

    while (true) {
        cout << "\nWelcome! Choose an option:\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1/2/3): ";
        cin >> choice;

        if (choice == 1) {
            signUp(users);
        }
        else if (choice == 2) {
            login(users);
        }
        else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}*/