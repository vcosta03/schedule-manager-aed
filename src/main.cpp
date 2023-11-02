#include <iostream>
#include <limits>
#include "Authentication.h"
#include "Lesson.h"
#include "Schedule.h"
#include "UcClass.h"
#include "Application.h"


int main(int argc, char* argv[]) {

//    Authentication auth;
//    auth.readUserDataCSV("../csvdata/userdata.csv");
//    auth.authMenu();

//    if (auth.isLogged()) {
        Application app;
        app.readFiles("../csvdata/classes_per_uc.csv", "../csvdata/classes.csv", "../csvdata/students_classes.csv");


        std::string option;
        while (option != "q") {

            std::cout << "\n---------------Main  Menu---------------\n";
            std::cout << "\t1. Student Information" << '\n';
            std::cout << "\t2. UC Information" << '\n';
            std::cout << "\t3. Schedules" << '\n';
            std::cout << "\t4. Make a new request" << '\n';


//            if (auth.getCurrentUser().isAdmin())
                std::cout << "\t5. Ticket Management " << '\n';


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
                case '5':
//                    if (!auth.getCurrentUser().isAdmin()) {
                        app.ticketHandling();
                        break;
//                    }
                case 'q':
                    break;

                default:
                    std::cout << "Choose a valid option." << std::endl;

                    break;
            }
//        }
    }

    return 0;
}
