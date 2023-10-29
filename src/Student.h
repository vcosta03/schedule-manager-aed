//
// Created by vascocosta on 10/29/23.
//

#ifndef AEDPROJECT_STUDENT_H
#define AEDPROJECT_STUDENT_H

#include <iostream>
#include <list>
#include "UcClass.h"
#include "Schedule.h"

class Student {
private:
    std::string name_, code_;
    std::list<UcClass> ucClasses_;
public:
    Student();
};


#endif //AEDPROJECT_STUDENT_H
