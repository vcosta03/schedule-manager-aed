//
// Created by vascocosta on 10/13/23.
//

#include "User.h"

User::User(std::string user, std::string pass, bool admin) : username(user), password(pass), isAdmin_(admin) {}

std::string User::get_username() {
    return username;
}

std::string User::get_password() {
    return password;
}

bool User::isAdmin() {
    return isAdmin_;
}

