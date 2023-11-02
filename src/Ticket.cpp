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

const Student &Ticket::getStudent() const {
    return student_;
}

bool Ticket::isEnrolled(const UcClass &ucClass) const {
    for (const auto& uc : student_.getUcClasses()) {
        if (uc == ucClass)
            return true;
    }
    return false;
}

bool Ticket::canEnroll(const UcClass &ucClass) const {
    for (const auto& studentUc : student_.getUcClasses()) {
        for (const auto& studentLesson : studentUc.getLessons()) {
            for (const auto& ucLesson : ucClass.getLessons()) {
                if (studentLesson.areOverlapping(ucLesson))
                    return false;
            }
        }
    }

    return true;
}

void Ticket::addUcClass() {
//    UcClass ucClassAdd;
//    if (type_ == 'a') {
//
//    }
//    if (isEnrolled(ucClasses_[0]) && canEnroll(ucClasses_[0])) {
//
//    }
}



