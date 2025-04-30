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

    while (password != users[username].password) {
        cout << "Incorrect password.\n";
        cout << "Re-enter your password: ";
        getline(cin, password);
    }

    if (password == users[username].password) {
        cout << "Welcome " << username << "!\n";
        if (users[username].role == "user") {
            cout << "Accessing User Functions...\n";
            userMenu();
        }
    }

}
void ConsoleApp::logout() {
    cout << "\n Logging out... See you next time!\n";
}


void ConsoleApp::userMenu() {
    int choice;
    string currentLoc, destination;

    do {
        cout << "\n--- User Menu ---\n";
        cout << "1. Add Graph\n2. View Map\n3. Find Shortest Route (Dijkstra)\n4. Traverse Graph (BFS/DFS)\n5. Add City\n6. Delete City\n7. Add Road\n8. Delete Road\n0. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            g.addGraph();
            break; 
        case 2:
            g.displayGraph();
            break;
        case 3:
            cout << "Enter your current city: ";
            cin >> ws; getline(cin, currentLoc);
            cout << "Enter destination city: ";
            getline(cin, destination);
            g.dijkstra(currentLoc, destination);
            break;
        case 4:
            g.traverseGraph();
            break;
        case 5:
            cout << "Enter city name: ";
            cin >> ws; getline(cin, c1);
            g.addCity(c1);
            break;
        case 6:
            cout << "Enter city name to delete: ";
            cin >> ws; getline(cin, c1);
            g.deleteCity(c1);
            break;
        case 7:
            cout << "Enter two cities and the distance: ";
            cin >> ws; 
            getline(cin, c1); getline(cin, c2);
            cout << "Enter distance: ";
            cin >> dist;
            g.addEdge(c1, c2, dist);
            break;
        case 8:
            cout << "Enter two cities to remove the road: ";
            cin >> ws; getline(cin, c1);
            getline(cin, c2);
            g.deleteEdge(c1, c2);
            break;
        case 0:
            logout();
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}