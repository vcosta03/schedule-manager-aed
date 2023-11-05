#include <iostream>
#include <limits>
#include "Authentication.h"
#include "Lesson.h"
#include "Schedule.h"
#include "UcClass.h"
#include "Application.h"

/** @file */

int main(int argc, char* argv[]) {
    bool bypassLogin = false;

//    "-a" flag para entrar automaticamente como admin

    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-a") {
            bypassLogin = true;
            break;
        }
    }

    Authentication auth;

    if (!bypassLogin) {
        auth.readUserDataCSV("../csvdata/userdata.csv");
        auth.authMenu();
    }


    if (auth.isLogged() || bypassLogin) {
        Application app;
        app.readFiles("../csvdata/classes_per_uc.csv", "../csvdata/classes.csv", "../csvdata/students_classes.csv", "../csvdata/syslog.csv");


        std::string option;
        while (option != "q") {

            std::cout << "\n---------------Main Menu----------------\n\n";
            std::cout << "\t1. Student Information" << '\n';
            std::cout << "\t2. UC Information" << '\n';
            std::cout << "\t3. Schedules" << '\n';
            std::cout << "\t4. Make a new request" << '\n';


            if (auth.getCurrentUser().isAdmin() || bypassLogin) {
            std::cout << "\t5. Ticket Management" << '\n';
            std::cout << "\t6. System Log\n";
            }

            std::cout << "\n\t\t\tPress q to exit" << '\n';
            std::cout << "----------------------------------------\n\n";


            std::cout << "> ";
            std::cin >> option;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (option.length() != 1) {
                std::cout << "Choose a valid option." << std::endl;
                continue;
            }

            switch (option[0]) {
                case '1':
                    app.students();
                    break;
                case '2':
                    app.ucInfo();
                    break;
                case '3':
                    app.schedules();
                    break;
                case '4':
                    app.tickets();
                    break;
                case '5': {
                    if (auth.getCurrentUser().isAdmin() || bypassLogin) {
                        app.ticketHandling();
                    }
                    else
                        std::cout << "Login to an Admin account to have access\nto this menu.\n";
                    break;
                }
                case '6': {
                    if (auth.getCurrentUser().isAdmin() || bypassLogin) {
                        app.sysLog();
                    }
                    else
                        std::cout << "Login to an Admin account to have access\nto this menu.\n";
                    break;
                }
                case 'q':
                    break;

                default:
                    std::cout << "Choose a valid option." << std::endl;
                    break;
            }
        }

        app.writeLog("../csvdata/syslog.csv");
    }



    return 0;
}
