#include<iostream>
#include<map>
#include<unordered_map>
#include<string>
#include <fstream>
#include "ConsoleApp.h"
#include "Graph.h"
#include <limits>
using namespace std;
ConsoleApp::ConsoleApp() {
    mainMenu();
}

void ConsoleApp::loadUsers() {
    // ifstream file("users.txt");
    // if (file.is_open()) {
    //     string username, password, role;
    //     while (file >> username >> password >> role) {
    //         users[username] = { password, role };
    //     }
    //     file.close();
    // }
}

void ConsoleApp::saveUsers() const {
    // ofstream file("users.txt");
    // for (const auto& pair : users) {
    //     file << pair.first << " " << pair.second << " " << endl;
    // }
    // file.close();
}

void ConsoleApp::signUp() {
    string username, password;
    cout << "Enter your username: ";
    cin >> ws;
    getline(cin, username);

    if (users.contains(username)) {
        cout << "Username already exists!\n";
        return;
    }

    cout << "Enter your password: ";
    getline(cin, password);
    User newUser(username, password);
    users[username] = newUser;
    cout << "Account created successfully for " << username << endl;
    users[username].graph.addGraph();
    userMenu(users[username]);
}

void ConsoleApp::login() {
    string username, password;

    cout << "Enter your username: ";
    cin >> ws;
    getline(cin, username);

    if (!users.contains(username)) {
        cout << "Username not found.\n";
        return;
    }

    cout << "Enter your password: ";
    getline(cin, password);

    while (password != users[username].getPassword()) {
        cout << "Incorrect password.\n";
        cout << "Re-enter your password: ";
        getline(cin, password);
    }

    if (password == users[username].getPassword()) {
        cout << "Welcome " << username << "!\n";
        userMenu(users[username]);
    }

}

void ConsoleApp::userMenu(User& thisUser) {
    //thisUser.getGraph().read();
    int choice;
    string currentLoc, destination;

    do {
        displayUserMenuOptions();
        choice = getValidatedMenuChoice(0, 7);

        try {
            executeUserMenuAction(choice, thisUser);
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    } while (choice != 0);

    //thisUser.getGraph().write();
}

void ConsoleApp::displayUserMenuOptions() {
    cout << "\n--- User Menu ---\n";
    cout << "1. View Map\n2. Find Shortest Route (Dijkstra)\n3. Traverse Graph (BFS/DFS)\n4. Add City\n5. Delete City\n6. Add Road\n7. Delete Road\n0. Logout\n";
    cout << "Enter your choice: ";
}

int ConsoleApp::getValidatedMenuChoice(int min, int max) {
    int choice;
    while (true) {
        if (!(cin >> choice) || choice < min || choice > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between " << min << " and " << max << ": ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

void ConsoleApp::executeUserMenuAction(int choice, User& thisUser) {
    string city1, city2;
    float distance;
    switch (choice) {
        case 1:
            thisUser.graph.displayGraph();
            break;
        case 2:
            try {
                cout << "Enter your current city: ";
                cin >> ws;
                getline(cin, city1);
                cout << "Enter destination city: ";
                getline(cin, city2);
                cout << thisUser.graph.dijkstra(city1, city2);
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        case 3:
            thisUser.graph.traverseGraph();
            break;
        case 4:
            try {
                cout << "Enter city name:\n";
                cin >> ws;
                getline(cin, city1);
                thisUser.graph.addCity(city1);
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        case 5:
            try {
                cout << "Enter city name to delete:\n";
                cin >> ws;
                getline(cin, city1);
                thisUser.graph.deleteCity(city1);
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        case 6:
            try {
                cout << "Enter first city name:\n";
                cin >> ws;
                getline(cin, city1);
                cout << "Enter second city name:\n";
                getline(cin, city2);
                cout << "Enter distance between them:\n";
                cin >> distance;
                thisUser.graph.addEdge(city1, city2, distance);
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        case 7:
            try {
                cout << "Enter first city name:\n";
                cin >> ws;
                getline(cin, city1);
                cout << "Enter second city name:\n";
                getline(cin, city2);
                thisUser.graph.deleteEdge(city1, city2);
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        case 0:
            cout << "Thank you for using this program!\nLogging out...\n";
            break;
        default:
            cout << "Invalid choice.\n";
    }
}


void ConsoleApp::mainMenu() {
    //loadUsers();
    int choice;

    while (true) {
        cout << "\nWelcome! Choose an option:\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            signUp();
        }
        else if (choice == 2) {
            login();
        }
        else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    //saveUsers();
}