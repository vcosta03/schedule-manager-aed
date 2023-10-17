//
// Created by vascocosta on 10/13/23.
//

#ifndef AEDPROJECT_USER_H
#define AEDPROJECT_USER_H

#include <stdio.h>
#include <iostream>

class User {
private:
    std::string username;
    std::string password;
    bool isAdmin_;

public:
    User(std::string user, std::string pass, bool admin);
    std::string get_username();
    std::string get_password();
    bool isAdmin();

};


#endif //AEDPROJECT_USER_H
