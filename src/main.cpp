#include <iostream>
#include "Authentication.h"
#include "Lesson.h"
#include "Schedule.h"


int main(int argc, char* argv[]) {
    Authentication auth;
    auth.readUserDataCSV("../csvdata/userdata.csv");
    auth.authMenu();

    if (auth.isLogged()) {
        char option;

        std::cout << "\n----------------Main Menu---------------\n";
        std::cout << "\t1. Student Information" << '\n';
        std::cout << "\t2. UC Information" << '\n';
        std::cout << "\t3. Schedules" << '\n';
        std::cout << "\t4. Make a new request" << '\n';


        if (auth.getCurrentUser().isAdmin())
            std::cout << "\t5. Tickets log (Admin-Only)" << '\n';


        std::cout << "\n\t\t\tPress q to exit" << s'\n';
        std::cout << "----------------------------------------\n\n";

        while (option != 'q') {
            std::cout << "> ";
            std::cin >> option;
            switch (option) {
                case '1':
                    option = 'q';
                    break;
                case '2':
                    option = 'q';
                    break;
                case 'q':
                    break;
                default:
                    std::cout << "Choose a valid option." << std::endl;
                    break;
            }
        }
    }

    return 0;
}
