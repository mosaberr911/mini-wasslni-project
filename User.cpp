//
// Created by Mohamed Yassin on 01/05/2025.
//

#include "User.h"

User::User() = default;

User::User(string username, string password) {
    this->username = username;
    this->password = password;
}

string User::getUsername() const {
    return this->username;
}

string User::getPassword() const {
    return this->password;
}

void User::setUsername(string username) {
    this->username = username;
}

void User::setPassword(string password) {
    this->password = password;
}