//
// Created by vascocosta on 10/25/23.
//

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Schedule.h"

Schedule::Schedule() = default;

Schedule::Schedule(const UcClass& ucClass) {
    lessons_.resize(5);
    ucClasses_.push_back(ucClass);
}

Schedule::Schedule(const Student &student) {
    lessons_.resize(5);

    for (const UcClass& uc : student.getUcClasses()) {
        ucClasses_.push_back(uc);
    }
}

/**
 * @brief Displays the Schedule.
 * @param type should be 0 to print an UcClass's Schedule and 1 to print a Student's Schedule.
 */

void Schedule::printSchedule(int type){
// PRINTA UCCLASS

    if (type == 0) {
        UcClass currUcClass = ucClasses_.at(0);


        for (const Lesson& lesson : currUcClass.getLessons()) {
            pushLesson(lesson, 'A');
        }

        std::cout << "\n----------------------------------------\n\n";
        std::cout << "UC: " << currUcClass.getUcId()
                << " | Class: " << currUcClass.getClassId() << "\n\n";

        for (int i = 0; i < 5; i++) {
            std::cout << '|' << std::setw(10) << dayWeek(i) << " |";

            for (const auto& pair : lessons_[i]) {
                std::string info = pair.second.getLessonType() + ' ' + pair.second.printTime();
                std::cout << ' ' << info << " |";
            }
            std::cout << '\n';
        }

        std::cout << '\n';
    }

//  PRINTA ESTUDANTE

    if (type == 1) {
        char index = 'A';


        std::cout << "Index for Uc/Classes pair:\n";

        for (const UcClass& uc : ucClasses_) {

            for (const Lesson& lesson : uc.getLessons()) {
                pushLesson(lesson, index);
            }

            std::cout << '\t' << index << ": " << uc.getUcId() << " - " << uc.getClassId() << '\n';
            index++;
        }

        std::cout << '\n';


        for (int i = 0; i < 5; i++) {
            std::cout << '|' << std::setw(10) << dayWeek(i) << " |";

            for (const auto& pair : lessons_[i]) {
                std::string info = std::string(1, pair.first) + ' ' + pair.second.getLessonType() + ' ' + pair.second.printTime();
                std::cout << ' ' << info << " |";
            }

            std::cout << '\n';
        }


    }


}


std::string Schedule::dayWeek(int day) const{
    switch (day) {
        case 0:
            return "Monday";
        case 1:
            return "Tuesday";
        case 2:
            return "Wednesday";
        case 3:
            return "Thursday";
        case 4:
            return "Friday";
        default:
            return "Invalid";
    }
}


/**
 * @brief Pushes a lesson to the correct list, sorted by start time.
 */
void Schedule::pushLesson(const Lesson &lesson, char index) {

    int weekday = lesson.getWeekday();
    auto it = lessons_[weekday].begin();

    while (it != lessons_[weekday].end()) {
        if (lesson.getStartTime() < it->second.getStartTime()) {
            break;
        }
        it++;
    }

    lessons_.at(lesson.getWeekday()).insert(it,std::pair<char, Lesson>(index, lesson) );
}






