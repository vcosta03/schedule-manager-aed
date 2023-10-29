//
// Created by vascocosta on 10/25/23.
//

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Schedule.h"

Schedule::Schedule() = default;

Schedule::Schedule(const UcClass& ucClass) {
    schedule_.resize(5);

    ucClasses_.push_back(ucClass);
}

Schedule::Schedule(const Student &student) {
    schedule_.resize(5);

    for (const UcClass& uc : student.getUcClasses()) {
        ucClasses_.push_back(uc);
    }
}


void Schedule::printSchedule(const int type){
// Printa UCCLASS horizontalmente

    if (type == 0) {
        UcClass currUcClass = ucClasses_.at(0);


        for (const Lesson& lesson : currUcClass.getLessons()) {
            pushLesson(lesson);
        }

        std::cout << "\n----------------------------------------\n\n";
        std::cout << "UC: " << currUcClass.getUcId()
                << " | Class: " << currUcClass.getClassId() << "\n\n";

        for (int i = 0; i < 5; i++) {
            std::cout << '|' << std::setw(10) << dayWeek(i) << " |";
            for (const auto& lessonInfo : schedule_[i]) {
                std::cout << ' ' << lessonInfo << " |";
            }
            std::cout << '\n';
        }

        std::cout << '\n';
    }

//  PRINTA ESTUDANTE

    if (type == 1) {
        char index = 'A';

        std::cout << "\n----------------------------------------\n\n";

        std::cout << "Index for Uc/Classes pair:\n";

        for (const UcClass& uc : ucClasses_) {

            for (const Lesson& lesson : uc.getLessons()) {
                pushLessonInfo(lesson, index);
            }

            std::cout << '\t' << index << ": " << uc.getUcId() << " - " << uc.getClassId() << '\n';
            index++;
        }

        std::cout << '\n';


        for (int i = 0; i < 5; i++) {
            std::cout << '|' << std::setw(10) << dayWeek(i) << " |";

            for (const auto& lessonInfo : schedule_[i]) {
                std::cout << ' ' << lessonInfo << " |";
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
            return "Friday;";
        default:
            return "Invalid";
    }
}


void Schedule::pushLesson(const Lesson &lesson) {
    std::string info = lesson.getLessonType() + ' ' +lesson.printTime();
    schedule_.at(lesson.getWeekday()).push_back(info);
}

void Schedule::pushLessonInfo(const Lesson &lesson, char index) {
    std::string i(1, index);
    std::string info = i + ' ' + lesson.getLessonType() + ' ' +lesson.printTime();
    schedule_.at(lesson.getWeekday()).push_back(info);
}






