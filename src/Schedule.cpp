//
// Created by vascocosta on 10/25/23.
//

#include <iostream>
#include "Schedule.h"

Schedule::Schedule() = default;

Schedule::Schedule(UcClass& ucClass) {
    lessons_.resize(5);
    ucClass_ = ucClass;
}

void Schedule::pushLesson(Lesson &lesson) {
    lessons_.at(lesson.getWeekday()).push_back(lesson);
}

void Schedule::printSchedule() {
    for (auto day : lessons_) {
        for (auto lesson : day) {
            std::cout << lesson.getWeekday() << '\n' << lesson.getStartTime() << '-' << lesson.getEndTime() << '\n' << '\n';
        }
    }
}


