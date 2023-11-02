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

    const Student& getStudent() const;

    void deleteUcClass();
    void addUcClass();
    void switchUcClasses();

    bool isEnrolled(const UcClass& ucClass) const;
    bool canEnroll(const UcClass& ucClass) const;

};


#endif //AEDPROJECT_TICKET_H
