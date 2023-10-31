#include <iostream>
#include <limits>
#include "Authentication.h"
#include "Lesson.h"
#include "Schedule.h"
#include "UcClass.h"
#include "Application.h"


int main(int argc, char* argv[]) {
    /*
     * bug: nao da pa dar cin num char, se input > 1 char, so le o primeiro logo pode ler mal; mudar todos pa string
     *
     *
     */





////    Authentication auth;
//    auth.readUserDataCSV("../csvdata/userdata.csv");
//    auth.authMenu();

//    if (auth.isLogged()) {

//    std::string userInput;
//    std::cout << "Please enter a line of text (press Enter to submit): ";
//    std::getline(std::cin, userInput);
//
//    if (userInput.empty()) {
//        std::cout << "You didn't enter any text." << std::endl;
//    } else {
//        std::cout << "You entered: " << userInput << std::endl;
//    }

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
//                std::cout << "\t5. Tickets log (Admin-Only)" << '\n';


            std::cout << "\n\t\t\tPress q to exit" << '\n';
            std::cout << "----------------------------------------\n\n";


            std::cout << "> ";
            std::cin >> option;

            if (option.length() != 1) {
                std::cout << "Choose a valid option." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                continue;
            }

            switch (option[0]) {
                case '1':
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    app.students();
                    break;
                case '2':
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    option = 'q';
                    break;
                case '3':
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    app.schedules();
                    break;
                case 'q':
                    break;

                default:
                    std::cout << "Choose a valid option." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    break;
            }
//        }
    }

    return 0;
}
