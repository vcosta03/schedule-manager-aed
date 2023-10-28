#include <iostream>
#include "Authentication.h"
#include "Lesson.h"
#include "Schedule.h"
#include "UcClass.h"


int main(int argc, char* argv[]) {
/*
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


        std::cout << "\n\t\t\tPress q to exit" << '\n';
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
*/
//    std::string t = "T", tp = "TP", pl = "PL", leic = "LEIC", turma = "05";
//    Lesson a(0, 930, 90, t), b(1, 1030, 60, pl), c(4, 1200, 30, tp) ;
//


    std::string leic = "LEIC", turma = "05";
    UcClass uc(leic, turma);

    Lesson lesson1(0, 800, 60, "T");
    Lesson lesson2(1, 900, 90, "TP");
    Lesson lesson3(2, 1000, 120, "PL");
    Lesson lesson4(3, 1100, 60, "T");
    Lesson lesson5(4, 1200, 90, "TP");
    Lesson lesson6(0, 1300, 120, "PL");
    Lesson lesson7(1, 1400, 60, "T");
    Lesson lesson8(2, 1500, 90, "TP");
    Lesson lesson9(3, 1600, 120, "PL");
    Lesson lesson10(4, 1700, 60, "T");

    // Create a vector to store the Lesson objects
    std::vector<Lesson> lessons = {lesson1, lesson2, lesson3, lesson4, lesson5, lesson6, lesson7, lesson8, lesson9, lesson10};

    for (const auto& lesson :  lessons) {
        uc.pushLesson(lesson);
    }

    Schedule schedule_uc(uc);
    schedule_uc.printSchedule(0);

    return 0;
}
