//
// Created by vascocosta on 10/25/23.
//

#ifndef AEDPROJECT_SCHEDULE_H
#define AEDPROJECT_SCHEDULE_H


#include <list>
#include <vector>
#include "UcClass.h"
#include "Lesson.h"
#include "Student.h"

/**
 * @brief Class to represent a schedule, used to display lesson information for UcClasses and Students.
 */

class Schedule {
private:
    /// Schedule's UcClasses, mainly useful for a Student.
    std::vector<UcClass> ucClasses_;
    /// Schedule's lessons organized in a vector with 5 lists, for each day of the week, sorted by time.
    std::vector<std::list<std::pair<char , Lesson>>> lessons_;

public:
    Schedule();
    Schedule(const UcClass& ucClass);
    Schedule(const Student& student);
    void pushLesson(const Lesson& lesson, char index);
    std::string dayWeek(int day) const;
    void printSchedule(int type);
};


#endif //AEDPROJECT_SCHEDULE_H
