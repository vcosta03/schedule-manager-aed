//
// Created by vascocosta on 11/1/23.
//

#include "Ticket.h"

Ticket::Ticket() = default;

Ticket::Ticket(Student &student, const char& type, const UcClass& ucClass) {
    student_ = student;
    ucClasses_.push_back(ucClass);
    processed_ = false;
    type_ = type;
}

Ticket::Ticket(Student &student,const char& type, const UcClass &from, const UcClass &to) {
    student_ = student;
    ucClasses_.push_back(from); //ucClasses[0] = from
    ucClasses_.push_back(to); //ucClasses[1] = to
    processed_ = false;
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

void Ticket::setProcessed(bool processed) {
    processed_ = processed;
}



