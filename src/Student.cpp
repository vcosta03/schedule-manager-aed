//
// Created by vascocosta on 10/29/23.
//

#include <map>
#include "Student.h"

Student::Student() {
    name_ = "";
    code_ = "";
}

Student::Student(std::string& code, std::string& name) {
    code_ = code;
    name_ = name;

}

const std::string &Student::getStudentName() const {
    return name_;
}

const std::string &Student::getStudentCode() const {
    return code_;
}

const std::list<UcClass> &Student::getUcClasses() const {
    return ucClasses_;
}

void Student::pushUcClass(const UcClass uc) {
    ucClasses_.push_back(uc);
}

bool Student::operator==(const Student &other) const {
    return name_ == other.getStudentName() || code_ == other.getStudentCode();
}

int Student::getCurricularYear() const {
    std::map<int, int> yearCounts;

    for (const UcClass& ucClass : ucClasses_) {
        std::string ucCode = ucClass.getUcId();
        int year = ucCode[ucCode.size() - 2] - '0';
        yearCounts[year]++;
    }

    int maxYear = -1;
    int maxCount = 0;

    for (const auto& pair : yearCounts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            maxYear = pair.first;
        }
    }

    return maxYear+1;
}

int Student::getUcsEnrolled() const {
    return ucClasses_.size();
}

bool Student::operator<(const Student &other) const {
    return code_ < other.getStudentCode();
}

void Student::setUcClasses(const std::list<UcClass> &ucClasses) {
    ucClasses_ = ucClasses;
}

void Student::setCode(const std::string &code) {
    code_ = code;
}

void Student::setName(const std::string &name) {
    name_ = name;
}

