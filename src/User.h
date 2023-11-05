//
// Created by vascocosta on 10/13/23.
//

#ifndef AEDPROJECT_USER_H
#define AEDPROJECT_USER_H

#include <stdio.h>
#include <iostream>

class User {
private:
    std::string username_;
    std::string password_;
    bool isAdmin_;

public:
    User(const std::string &username, const std::string& password, bool admin);
    const std::string getUsername() const;
    const std::string getPassword() const;
    bool isAdmin() const;

};


#endif //AEDPROJECT_USER_H
