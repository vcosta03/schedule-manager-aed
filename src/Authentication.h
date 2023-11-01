//
// Created by vascocosta on 10/13/23.
//

#ifndef AEDPROJECT_AUTHENTICATION_H
#define AEDPROJECT_AUTHENTICATION_H

#include <iostream>
#include <list>
#include "User.h"

class Authentication {
private:
    User currentUser;
    bool isLogged_;
    std::list<User> users;
    std::string userDataCSV;

    void loginUser();
    void registerUser();
    bool userExists(std::string username, std::string password);
    void writeUserDataCSV(User user);
public:
    Authentication();
    void readUserDataCSV(const std::string& filename);
    void authMenu();
    bool isLogged();
    User getCurrentUser();
};


#endif //AEDPROJECT_AUTHENTICATION_H
