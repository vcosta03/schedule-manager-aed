//
// Created by vascocosta on 10/25/23.
//

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Schedule.h"

Schedule::Schedule() = default;

Schedule::Schedule(UcClass& ucClass) {
    lessons_.resize(5);
    for (const Lesson& lesson : ucClass.getLessons()) {
        pushLesson(lesson);
    }

    ucClasses_.push_back(ucClass);
}

void Schedule::pushLesson(const Lesson &lesson) {
    lessons_.at(lesson.getWeekday()).push_back(lesson);
}

void Schedule::printSchedule(const int type) {
    // "---------------|" string tem tamanho 16, std::setw(16) e dps escrever
/*
    std::cout << "UcClass/Student Schedule\n\n";
    std::cout << "|---------------|---------------|---------------|---------------|---------------|---------------|\n";
    std::cout << '|' << std::setfill(' ') << std::setw(16) << "Time |"
                << std::setw(16) << "Monday |"
                << std::setw(16) << "Tuesday |"
                << std::setw(16) << "Wednesday |"
                << std::setw(16) << "Thursday |"
                << std::setw(16) << "Friday |" << '\n';
    std::cout << "|---------------|---------------|---------------|---------------|---------------|---------------|\n";

    int hours = 8;
    int minutes = 0;
    while (hours <= 18) {
        int currTime = hours * 100 + minutes;
        std::string strCurrTime = std::to_string(currTime/100) + ':' + (currTime%100 < 10 ? '0' + std::to_string(currTime%100) : std::to_string(currTime%100));
        std::cout << '|' << std::setw(16) << '|'
                << std::setw(16) << '|'
                << std::setw(16) << '|'
                << std::setw(16) << '|'
                << std::setw(16) << '|'
                << std::setw(16) << '|' << '\n';

        std::cout << '|' << std::setfill(' ') << std::setw(14) << strCurrTime << " |";

        std::cout << std::setfill(' ')
                  << std::setw(16) << "Monday |"
                  << std::setw(16) << "Tuesday |"
                  << std::setw(16) << "Wednesday |"
                  << std::setw(16) << "Thursday |"
                  << std::setw(16) << "Friday |" << '\n';

        yieldsTime(hours, minutes);

    }
    std::cout << "|---------------|---------------|---------------|---------------|---------------|---------------|\n";

*/

// Printa UCCLASS horizontalmente

    if (type == 0) {
        std::cout << "UC: " << ucClasses_.at(0).getUcId()
                << " | Class: " << ucClasses_.at(0).getClassId() << "\n\n";

        for (int i = 0; i < 5; i++) {
            std::cout << '|' << std::setw(10) << dayWeek(i) << " |";
            for (const auto& lesson : lessons_[i]) {
                std::cout << ' ' << lesson.getLessonType() << ' ' << lesson.printTime() << " |";
            }

            std::cout << '\n';
        }
    }

    if (type == 1) {
        std::cout << "Ainda nao esta pronto burro\n";
    }


}

void Schedule::yieldsTime(int &hour, int &min) const {
    min += 30;
    if (min == 60) {
        hour++;
        min = 0;
    }
}

std::string Schedule::dayWeek(int day) {
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



