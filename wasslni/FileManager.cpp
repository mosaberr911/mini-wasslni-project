#include "FileManager.h"
#include "User.h"
#include "Graph.h"
#include "UserManager.h"
#include <QDebug>
#include <QString>
#include <regex>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

FileManager::FileManager() = default;

void FileManager::saveGraphToFile(const string &filePath, User& targetUser) {

    try {
        deleteUserGraph(filePath, targetUser); // Clean existing graph data
    } catch (const exception& e) {
        qWarning() << "Error during deletion: " << e.what();
        // Continue with the save operation despite deletion error
    }
    vector<string> graphLines = targetUser.getConvertedAdjacencyList();

    ofstream outFile(filePath, ios::app);  // Append only

    if (!outFile) {
        qWarning() << "ERROR: Failed to open file for writing: " << filePath;
        // Try creating the directory if it doesn't exist
        string dirPath = filePath.substr(0, filePath.find_last_of("/\\"));

        // Try opening with create flag
        ofstream createFile(filePath, ios::app | ios::out);
        if (!createFile) {
            throw runtime_error("CRITICAL ERROR: Still cannot create file even with create flag");
        }
        outFile = std::move(createFile);
    }

    outFile << "# " << targetUser.getEmail() << "\n";
    for (const string& line : graphLines) {
        outFile << line << "\n";
    }

    if (!graphLines.empty()) {
        outFile << "\n";  // Optional separator only if we added data
    }

    outFile.close();

    // Verify the file was written correctly
    ifstream checkFile(filePath);
    if (checkFile) {
        string content((istreambuf_iterator<char>(checkFile)), istreambuf_iterator<char>());
        checkFile.close();
    } else {
        qWarning() << "Warning: Could not verify file contents after writing\n";
    }
}

void FileManager::deleteUserGraph(const string &filePath, User &targetUser) {

    // Try to create file if it doesn't exist to avoid errors
    if (!fileExists(filePath)) {
        ofstream createFile(filePath);
        if (createFile) {
            createFile.close();
        } else {
            throw runtime_error("Failed to create non-existent file");
        }
    }

    ifstream inFile(filePath);
    vector<string> lines;
    string line;
    bool isTargetUser = false;
    int lineCount = 0;
    int skippedLines = 0;

    if (!inFile) {
        // Create an empty file instead of failing
        ofstream newFile(filePath, ios::trunc);
        if (newFile) {
            newFile.close();
        } else {
            throw runtime_error("ERROR: Unable to create or open file: " + filePath);
        }
        return;
    }
    while (getline(inFile, line)) {
        lineCount++;

        if (!line.empty() && line[0] == '#') {
            // Found a user marker, check if it's our target
            string email = line.substr(1);
            email.erase(0, email.find_first_not_of(" \t"));
            email.erase(email.find_last_not_of(" \t") + 1);

            if (email == targetUser.getEmail()) {
                isTargetUser = true; // Start skipping lines
                skippedLines++;
                continue;
            } else {
                isTargetUser = false; // Stop skipping, this is a different user
            }
        }

        // Only keep lines that don't belong to the target user
        if (!isTargetUser) {
            lines.push_back(line);
        } else {
            skippedLines++;
        }
    }
    inFile.close();

    ofstream outFile(filePath, ios::trunc);
    if (!outFile) {
        throw runtime_error("ERROR: Unable to open file for writing: " + filePath);
    }

    for (const string& l : lines) {
        outFile << l << '\n';
    }
    outFile.close();

    // Check if file exists and has correct content
    ifstream verifyFile(filePath);
    if (verifyFile) {
        string content((istreambuf_iterator<char>(verifyFile)), istreambuf_iterator<char>());
        verifyFile.close();
    } else {
        throw runtime_error("WARNING: Could not verify file contents after deletion\n");
    }
}

bool FileManager::fileExists(const string& path) {
    ifstream f(path);
    return f.good();
}

void FileManager::loadGraphFromFile(const string &filePath, const string& email) {
    ifstream inFile(filePath);
    vector<string> graphLines;
    string line;
    bool isTargetUser = false;

    if (!inFile) {
        qWarning() << "ERROR: Could not open file.\n";
    }

    while (getline(inFile, line)) {
        if (!line.empty() && line[0] == '#') {
            string targetEmail = line.substr(1);
            targetEmail.erase(0, targetEmail.find_first_not_of(" \t"));
            targetEmail.erase(targetEmail.find_last_not_of(" \t") + 1);

            // Early exit if new user section starts after our target
            if (isTargetUser) break;

            isTargetUser = (targetEmail == email);
            continue;
        }

        if (isTargetUser && !line.empty()) {
            graphLines.push_back(line);
        }
    }

    inFile.close();

    User targetUser = UserManager::getUserByEmail(email);
    targetUser.parseLoadedGraphLines(graphLines);
    UserManager::updateUser(targetUser);
}

unordered_map<string, User> FileManager::loadUsers(const string &filePath) {
    unordered_map<string, User> users;
    ifstream file(filePath);

    if (!file.is_open()) {
        throw runtime_error("ERROR: File not found or could not open for reading");
    }

    try {
        string line;
        while (getline(file, line)) {
            size_t comma_pos = line.find(',');
            if (comma_pos == string::npos || comma_pos == 0 || comma_pos == line.length() - 1) {
                continue;
            }

            string email = line.substr(0, comma_pos);
            string password = line.substr(comma_pos + 1);

            // Basic validation
            if (email.empty() || password.empty()) {
                continue;
            }

            if (email.length() > 254 || password.length() > 100) {
                continue;
            }

            users[email] = User(email, password);
        }
    } catch (const exception& e) {
        file.close();
        users.clear();
        throw runtime_error("ERROR: Failed to read users data: " + string(e.what()));
    }

    file.close();
    return users;
}

void FileManager::saveUsers(const string &filePath, const unordered_map<string, User>& users) {
    ofstream file(filePath, ios::trunc);  // Truncate existing file

    if (!file.is_open())
        throw runtime_error("ERROR: Could not open file for saving");

    try {
        for (const auto& pair : users) {
            const string& email = pair.first;
            const string& password = pair.second.getPassword();

            // Basic validation before writing
            if (email.empty() || password.empty()) {
                continue;
            }

            if (email.find(',') != string::npos) {
                continue;
            }

            file << email << "," << password << "\n";

            if (file.fail()) {
                throw runtime_error("Failed to write user data for: " + email);
            }
        }
    } catch (const exception& e) {
        file.close();
        throw runtime_error("ERROR: Failed to save user data: " + string(e.what()));
    }

    file.close();
}
