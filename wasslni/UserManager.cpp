#include "UserManager.h"
#include "PathManager.h"
#include <iostream>

UserManager::UserManager() = default;

unordered_map<string, User> UserManager::users;

bool UserManager::checkUserCredentials(const string& email, const string& password) {
    return containsUser(email) && users[email].getPassword() == password;
}

bool UserManager::containsUser(const string& email) {
    return users.find(email) != users.end();
}

User UserManager::getUserByEmail(const string& email) {
    auto it = users.find(email);
    if (it == users.end()) {
        throw std::invalid_argument("User not found: " + email);
    }
    return it->second;
}

void UserManager::loadUsersData() {
    users = FileManager::loadUsers(PathManager::getUsersFilePath());
}

void UserManager::saveUsersData() {
    FileManager::saveUsers(PathManager::getUsersFilePath(), users);
}

void UserManager::registerUser(const string &email, const string &password) {
    if (containsUser(email)) {
        throw std::invalid_argument("User already exists: " + email);
    }
    users[email] = User(email, password);
}

void UserManager::updateUser(const User& user) {
    std::lock_guard<std::mutex> lock(mutex);
    if (!containsUser(user.getEmail())) {
        throw std::invalid_argument("User does not exist: " + user.getEmail());
    }
    users[user.getEmail()] = user;
}

void UserManager::saveUserGraph(const string& email, const string& filePath) {
    FileManager::saveGraphToFile(filePath, users[email]);
}

void UserManager::loadUserGraph(const string& filePath, const string& email) {
    FileManager::loadGraphFromFile(filePath, email);
}

void UserManager::displayUsersData() {
    for (auto& [email, user] : users) {
        cout << "Users Email: " + email << endl;
    }
}
