//
// Created by vascocosta on 10/13/23.
//

#include "Authentication.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>

Authentication::Authentication() : currentUser("1", "1", false), userDataCSV(""), isLogged_(false) {}

void Authentication::authMenu() {
    char option;

    std::cout << "-------------Authentication-------------" << std::endl;
    std::cout << "Welcome to LEIC Schedule Manager!\n\nPlease Log in or Register:" << std::endl;
    std::cout << "\t1. Login" << std::endl;
    std::cout << "\t2. Register\n" << std::endl;
    std::cout << "\t\t\tPress q to exit" << std::endl;
    std::cout << "----------------------------------------\n" << std::endl;

    while (option != 'q') {
        std::cout << "> ";
        std::cin >> option;
        switch (option) {
            case '1':
                option = 'q';
                loginUser();
                break;
            case '2':
                option = 'q';
                registerUser();
                break;
            case 'q':
                return;
            default:
                std::cout << "Choose a valid option." << std::endl;
                break;
        }
    }

}

void Authentication::loginUser() {
    std::string username, password;

    std::cout << "\n-----------------Login------------------" << std::endl;
    std::cout << "\tEnter your username: "; std::cin >> username;
    std::cout << "\tEnter your password: "; std::cin >> password;

    if (userExists(username, password)) {
        isLogged_ = true;
        std::cout << "----------------------------------------\n\n";
        std::cout << "\t\t\tWelcome " << username << "!" << std::endl;
    }

    else {
        isLogged_ = false;
        std::cout << "\nInvalid username/password combination. " << std::endl;
    }

}

void Authentication::registerUser() {
    std::string username, password;
    bool isAdmin;

    std::cout << "----------------Register----------------" << std::endl;
    std::cout << "\tEnter your new username: "; std::cin >> username;
    std::cout << "\tEnter your new password: "; std::cin >> password;
    std::cout << "\tAdmin account (1 - Yes, 0 - No): "; std::cin >> isAdmin; //bug: se input for algo sem ser 0 e 1 da loop infinito


    if (!userExists(username, password)) {
        User newUser = User(username, password, isAdmin);
        users.push_back(newUser);
        writeUserDataCSV(newUser);

        std::cout << "----------------------------------------\n\n";
        std::cout << "\tYou're now registered as " << username << "!\n" << std::endl;
    }

    else {
        std::cout << "----------------------------------------\n\n";
        std::cout << username << " already exists!\n" << std::endl;    }


    authMenu();
}

bool Authentication::userExists(std::string username, std::string password) {
    for (auto user : users) {
        if (username == user.get_username() && password == user.get_password()) {
            currentUser = user;
            return true;
        }
    }
    return false;
}

bool Authentication::isLogged() {
    return isLogged_;
}

User Authentication::getCurrentUser() {
    return currentUser;
}

void Authentication::readUserDataCSV(const std::string& filename) {
    userDataCSV = filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the CSV file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string username, password, isAdminStr;
        bool isAdmin;

        if (std::getline(ss, username, ',') && std::getline(ss, password, ',') && std::getline(ss, isAdminStr)) {
            isAdmin = (isAdminStr == "1");
            User newUser(username, password, isAdmin);
            users.push_back(newUser);

        } else {
            std::cerr << "Invalid line in the CSV file: " << line << std::endl;
        }
    }

    file.close();
}

void Authentication::writeUserDataCSV(User user) {
    std::ofstream file(userDataCSV, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Failed to open the CSV file for writing." << std::endl;
        return;
    }

    file << user.get_username() << "," << user.get_password() << "," << (user.isAdmin() ? "1" : "0") << "\n";

    file.close();
}

