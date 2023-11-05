//
// Created by vascocosta on 10/13/23.
//

#ifndef AEDPROJECT_AUTHENTICATION_H
#define AEDPROJECT_AUTHENTICATION_H

#include <iostream>
#include <list>
#include "User.h"

/**
 * @brief Stores user data and handles user sessions.
 *
 * Fundamental component of the program to handle user authentication and access control, it further enables admin restricted
 * functionalities on the main application.
 */

class Authentication {
private:
    User currentUser;
    bool isLogged_;
    std::list<User> users;
    std::string userDataCSV;

public:
    Authentication();

    bool isLogged();
    User getCurrentUser();

    void authMenu();

    void loginUser();
    void registerUser();
    void readUserDataCSV(const std::string& filename);
    void writeUserDataCSV(User user);

    bool userExists(std::string username, std::string password);
};


#endif //AEDPROJECT_AUTHENTICATION_H
