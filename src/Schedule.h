//
// Created by vascocosta on 10/25/23.
//

#ifndef AEDPROJECT_SCHEDULE_H
#define AEDPROJECT_SCHEDULE_H


#include <list>
#include <vector>
#include "UcClass.h"
#include "Lesson.h"

class Schedule {
private:
    std::vector<std::list<Lesson>> lessons_;
public:
    Schedule();
    Schedule(UcClass& ucClass);
//    Schedule(Student& student);
    void pushLesson(const Lesson& lesson); // quero que automaticamente construa a partir dos vetores de liçao de uc e de student
    void printSchedule();
};


#endif //AEDPROJECT_SCHEDULE_H
