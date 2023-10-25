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

std::string UcClass::getUcId() const {
    return ucId_;
}

std::string UcClass::getClassId() const {
    return classId_;
}

//Schedule UcClass::getSchedule() const {
//    return schedule_;
//}
//
//Schedule UcClass::getSchedule() const {
//    return schedule_;
//}

