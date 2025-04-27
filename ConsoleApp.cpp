#include<iostream>
#include<map>
#include<unordered_map>
#include<string>
#include <fstream>
#include "ConsoleApp.h"
#include "Graph.h"
#include <limits> 
Graph g;
using namespace std;

ConsoleApp::ConsoleApp() {
    loadUsers();
}

void ConsoleApp::loadUsers() {
    unordered_map<string, User> users;
    ifstream file("users.txt");
    if (file.is_open()) {
        string username, password, role;
        while (file >> username >> password >> role) {
            users[username] = { password, role };
        }
        file.close();
    }
}

void ConsoleApp::saveUsers() const {
    ofstream file("users.txt");
    for (const auto& pair : users) {
        file << pair.first << " " << pair.second.password << " " << pair.second.role << endl;
    }
    file.close();
}

void ConsoleApp::signUp() {
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
    saveUsers();
    cout << "Account created successfully for " << username << " as " << role << ".\n";
}

void ConsoleApp::login() {
    string username, password;

    cout << "Enter your username: ";
    cin >> ws;
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
            cout << "Accessing Admin Functions...\n";
            // adminMenu(); // <<== you can call Admin Menu here
        }
        else {
            cout << "Accessing User Functions...\n";
            // userMenu(); // <<== you can call User Menu here
        }
    }
    else {
        cout << "Incorrect password.\n";
        string forgot;
        cout << "Forgot your password? (yes/no): ";
        cin >> forgot;
        if (forgot == "yes") {
            cout << "Reset Password Function (Placeholder)\n";
        }
    }

}

void ConsoleApp::adminMenu() {
    int choice;
    string c1, c2;
    float dist;

    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add City\n2. Delete City\n3. Add Road\n4. Delete Road\n5. View Map\n0. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter city name: ";
            cin >> ws; getline(cin, c1);
            g.addCity(c1);
            break;
        case 2:
            cout << "Enter city name to delete: ";
            cin >> ws; getline(cin, c1);
            g.deleteCity(c1);
            break;
        case 3:
            cout << "Enter two cities and the distance: ";
            cin >> ws; 
            getline(cin, c1); getline(cin, c2);
            cout << "Enter distance: ";
            cin >> dist;
            g.addEdge(c1, c2, dist);
            break;
        case 4:
            cout << "Enter two cities to remove the road: ";
            cin >> ws; getline(cin, c1);
            getline(cin, c2);
            g.deleteEdge(c1, c2);
            break;
        case 5:
            g.displayGraph();
            break;
        case 0:
            cout << "Logging out of Admin Menu.\n";////////////////mestany ashraf yekhalas el logout///////////////////
            break;
        default:
            cout << "Invalid choice.\n";
            }
        }

    } while (choice != 0);
}

void ConsoleApp::userMenu() {
    int choice;
    string currentLoc, destination;

    do {
        cout << "\n--- User Menu ---\n";
        cout << "1. View Map\n2. Find Shortest Route (Dijkstra)\n3. Traverse Graph (BFS/DFS)\n0. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            g.displayGraph();
            break;
        case 2:
            cout << "Enter your current city: ";
            cin >> ws; getline(cin, currentLoc);
            cout << "Enter destination city: ";
            getline(cin, destination);
            g.dijkstra(currentLoc, destination);
            break;
        case 3:
            g.traverseGraph();
            break;
        case 0:
            cout << "Logging out of User Menu.\n";////////////////mestany ashraf yekhalas el logout///////////////////
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}