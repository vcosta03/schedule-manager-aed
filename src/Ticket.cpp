//
// Created by vascocosta on 11/1/23.
//

#include "Ticket.h"

Ticket::Ticket() = default;

Ticket::Ticket(Student &student, const char& type, const UcClass& ucClass) {
    student_ = student;
    ucClasses_.push_back(ucClass);
    type_ = type;
}

Ticket::Ticket(Student &student,const char& type, const UcClass &from, const UcClass &to) {
    student_ = student;
    ucClasses_.push_back(from);
    ucClasses_.push_back(to);
    type_ = type;
}

Student &Ticket::getStudent() {
    return student_;
}


const std::vector<UcClass> Ticket::getUcClasses() const {
    return ucClasses_;
}

const char &Ticket::getType() const {
    return type_;
}



