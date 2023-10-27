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

const std::string UcClass::getUcId() const {
    return ucId_;
}

const std::string UcClass::getClassId() const {
    return classId_;
}

const std::vector<Lesson> UcClass::getLessons() const {
    return lessons_;
}

void UcClass::pushLesson(const Lesson& lesson) {
    lessons_.push_back(lesson);
}

