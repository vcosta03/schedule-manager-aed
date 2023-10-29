//
// Created by vascocosta on 10/20/23.
//

#include <fstream>
#include <iostream>
#include "UcClass.h"

UcClass::UcClass() = default;

UcClass::UcClass(std::string& ucId, std::string& classId) {
    ucId_ = ucId;
    classId_ = classId;
}


std::vector<Lesson> UcClass::getLessons() const {
    return lessons_;
}

void UcClass::pushLesson(const Lesson& lesson) {
    lessons_.push_back(lesson);
}

bool UcClass::operator<(const UcClass &other) const {
    if (ucId_ != other.getUcId()) {
        return ucId_ < other.getUcId();
    }
    return classId_ < other.getClassId();

}

bool UcClass::operator==(const UcClass &other) const {
    return ucId_ == other.getUcId() && classId_ == other.getClassId();
}

const std::string &UcClass::getUcId() const {
    return ucId_;
}

const std::string &UcClass::getClassId() const {
    return classId_;
}



