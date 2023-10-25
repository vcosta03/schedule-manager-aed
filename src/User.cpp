//
// Created by vascocosta on 10/13/23.
//

#include "User.h"

User::User(std::string username, std::string password, bool admin) : username_(username), password_(password), isAdmin_(admin) {}

std::string User::get_username() {
    return username_;
}

std::string User::get_password() {
    return password_;
}

bool User::isAdmin() {
    return isAdmin_;
}

