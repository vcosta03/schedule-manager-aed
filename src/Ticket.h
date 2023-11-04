//
// Created by vascocosta on 11/1/23.
//

#ifndef AEDPROJECT_TICKET_H
#define AEDPROJECT_TICKET_H

#include <iostream>
#include "Student.h"
#include "Lesson.h"

class Ticket {
private:
    Student student_;
    std::vector<UcClass> ucClasses_;
    bool processed_;
    char type_; // a = add; d = delete; s = switch

public:
    Ticket();
    Ticket(Student& student, const char& type, const UcClass& ucClass);
    Ticket(Student& student, const char& type, const UcClass& from, const UcClass& to);

    Student& getStudent();
    const std::vector<UcClass> getUcClasses() const;
    const char& getType() const;

    void setProcessed(bool processed);
};


#endif //AEDPROJECT_TICKET_H
