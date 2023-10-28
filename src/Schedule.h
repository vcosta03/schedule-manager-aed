//
// Created by vascocosta on 10/25/23.
//

#ifndef AEDPROJECT_SCHEDULE_H
#define AEDPROJECT_SCHEDULE_H


#include <list>
#include <vector>
#include <map>
#include "UcClass.h"
#include "Lesson.h"

class Schedule {
private:
    std::vector<UcClass> ucClasses_;
//    std::map<UcClass, std::vector<Lesson>> U;
    std::vector<std::vector<Lesson>> lessons_;
public:
    Schedule();
    Schedule(UcClass& ucClass);
//    Schedule(Student& student);
    void pushLesson(const Lesson& lesson); // quero que automaticamente construa a partir dos vetores de liçao de uc e de student
    void yieldsTime(int& hour, int& min) const;
    std::string dayWeek(int day);
    void printSchedule(const int type);
};


#endif //AEDPROJECT_SCHEDULE_H
