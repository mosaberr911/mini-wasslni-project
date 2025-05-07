//
// Created by Mohamed Yassin on 04/05/2025.
//

#include "FileSystem.h"
#include "User.h"
#include "Graph.h"
#include <regex>
#include <sstream>
#include <fstream>
using namespace std;

FileSystem::FileSystem() = default;

vector<string> FileSystem::convertAdjListToGraphLines(AdjacencyList adj) {
    vector<string> graphLines;

    for (const auto& [city, neighbors] : adj) {
        string line = city;

        for (const auto& [neighbor, distance] : neighbors) {
            line += " (" + neighbor + ":" + to_string(distance) + ")";
        }

        graphLines.push_back(line);
    }

    return graphLines;
}

AdjacencyList FileSystem::parseGraphLines(const vector<string> &graphLines) {
    AdjacencyList graph;
    regex pattern(R"(\(([^:]+):([0-9]+(?:\.[0-9]+)?)\))");  // matches (city:float)

    for (const string& line : graphLines) {
        istringstream iss(line);
        string city;
        iss >> city; // Extract source city

        // Extract all (destination:distance) pairs
        auto matches_begin = sregex_iterator(line.begin(), line.end(), pattern);
        auto matches_end = sregex_iterator();

        for (sregex_iterator i = matches_begin; i != matches_end; ++i) {
            smatch match = *i;
            string destCity = match[1];
            float weight = stof(match[2]);

            graph[city].emplace_back(destCity, weight);
        }
    }

    return graph;
}

void FileSystem::saveGraphToFile(const string& filename, User& targetUser) {
    try {
        deleteUserGraph(filename, targetUser); // Clean existing graph data
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    vector<string> graphLines = convertAdjListToGraphLines(targetUser.graph.getAdjacencyList());

    ofstream outFile(filename, ios::app);  // Append only
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    outFile << "# " << targetUser.getUsername() << "\n";
    for (const string& line : graphLines) {
        outFile << line << "\n";
    }
    outFile << "\n";  // Optional separator

    outFile.close();
}

void FileSystem::loadGraphFromFile(const string& filename, User& targetUser) {

    ifstream inFile(filename);
    vector<string> graphLines;
    string line;
    bool isTargetUser = false;

    if (!inFile) {
        cerr << "Error: Could not open file.\n";
    }

    while (getline(inFile, line)) {
        if (!line.empty() && line[0] == '#') {
            string targetUsername = line.substr(1);
            targetUsername.erase(0, targetUsername.find_first_not_of(" \t"));
            targetUsername.erase(targetUsername.find_last_not_of(" \t") + 1);

            // Early exit if new user section starts after our target
            if (isTargetUser) break;

            isTargetUser = (targetUsername == targetUser.getUsername());
            continue;
        }

        if (isTargetUser && !line.empty()) {
            graphLines.push_back(line);
        }
    }

    inFile.close();

    AdjacencyList userAdjacencyList;
    userAdjacencyList = parseGraphLines(graphLines);
    targetUser.graph.setAdjacencyList(userAdjacencyList);
}

void FileSystem::deleteUserGraph(const string& filename, User& targetUser) {
    ifstream inFile(filename);
    vector<string> lines;
    string line;
    bool isTargetUser = false;

    if (!inFile) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    while (getline(inFile, line)) {
        if (!line.empty() && line[0] == '#') {
            string username = line.substr(1);
            username.erase(0, username.find_first_not_of(" \t"));
            username.erase(username.find_last_not_of(" \t") + 1);

            isTargetUser = (username == targetUser.getUsername());
            continue;
        }

        if (!isTargetUser) {
            lines.push_back(line);
        }
    }

    inFile.close();

    ofstream outFile(filename, ios::trunc);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for (const string& l : lines) {
        outFile << l << '\n';
    }

    outFile.close();
}

unordered_map<string, User> FileSystem::loadUsers(const string& filename) {
    unordered_map<string, User> users;
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        cout << "Note: File not found or could not be opened for reading: " << filename << std::endl;
        cout << "Creating a new empty user database." << std::endl;
        // File doesn't exist yet, which is fine for a new system
    }

    // Read number of users
    size_t numUsers;
    file.read(reinterpret_cast<char*>(&numUsers), sizeof(numUsers));

    if (file.fail()) {
        cout << "Error: Failed to read number of users from file" << std::endl;
        file.close();
    }

    // Read each user
    for (size_t i = 0; i < numUsers && !file.eof(); ++i) {
        // Read username
        size_t usernameLength;
        file.read(reinterpret_cast<char*>(&usernameLength), sizeof(usernameLength));

        if (file.fail()) {
            cout << "Error: Failed to read username length for user #" << i << std::endl;
            file.close();
        }

        string username(usernameLength, '\0');
        file.read(&username[0], usernameLength);

        if (file.fail()) {
            cout << "Error: Failed to read username data for user #" << i << std::endl;
            file.close();
        }

        // Read password
        size_t passwordLength;
        file.read(reinterpret_cast<char*>(&passwordLength), sizeof(passwordLength));

        if (file.fail()) {
            cout << "Error: Failed to read password length for user #" << i << std::endl;
            file.close();
        }

        string password(passwordLength, '\0');
        file.read(&password[0], passwordLength);

        if (file.fail() && !file.eof()) {
            std::cout << "Error: Failed to read password data for user #" << i << std::endl;
            file.close();
        }

        // Add user to map
        users[username] = User(username, password);
    }

    file.close();
    return users;
}

void FileSystem::saveUsers(const string& filename, const unordered_map<string, User> users) {
    ofstream file(filename, ios::binary | ios::trunc);

    if (!file.is_open()) {
        cout << "Error: Could not open file for writing: " << filename << std::endl;
    }

    // Write number of users
    size_t numUsers = users.size();
    file.write(reinterpret_cast<const char*>(&numUsers), sizeof(numUsers));

    // Write each user
    for (const auto& pair : users) {
        const User& user = pair.second;

        // Write username length and data
        string username = user.getUsername();
        size_t usernameLength = username.length();
        file.write(reinterpret_cast<const char*>(&usernameLength), sizeof(usernameLength));
        file.write(username.c_str(), usernameLength);

        // Write password length and data
        string password = user.getPassword();
        size_t passwordLength = password.length();
        file.write(reinterpret_cast<const char*>(&passwordLength), sizeof(passwordLength));
        file.write(password.c_str(), passwordLength);
    }

    file.flush();
    file.close();

    if (file.fail()) {
        cout << "Error: Failed to save data to file" << std::endl;
    }
}