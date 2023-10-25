//
// Created by vascocosta on 10/25/23.
//

#ifndef AEDPROJECT_SCHEDULE_H
#define AEDPROJECT_SCHEDULE_H


#include <list>
#include <vector>
#include "Lesson.h"

class Schedule {
private:
    UcClass ucClass_;
    std::vector<std::list<Lesson>> lessons_;
public:
    Schedule();
    Schedule(UcClass& ucClass);
    void pushLesson(Lesson& lesson);
    void printSchedule();
};


#endif //AEDPROJECT_SCHEDULE_H
