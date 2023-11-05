//
// Created by vascocosta on 10/13/23.
//

#include "User.h"

User::User(const std::string &username, const std::string &password, bool admin) : username_(username), password_(password), isAdmin_(admin) {}

const std::string User::getUsername() const{
    return username_;
}

const std::string User::getPassword() const{
    return password_;
}

bool User::isAdmin() const{
    return isAdmin_;
}

