//
// Created by vascocosta on 10/29/23.
//

#ifndef AEDPROJECT_STUDENT_H
#define AEDPROJECT_STUDENT_H

#include <iostream>
#include <list>
#include "UcClass.h"

class Student {
private:
    std::string name_, code_;
    std::list<UcClass> ucClasses_;

public:
    Student();
    Student(std::string& code, std::string& name);

    const std::string &getStudentName() const;
    const std::string &getStudentCode() const;
    const std::list<UcClass> &getUcClasses() const;

    void pushUcClass(const UcClass uc);
    int getCurricularYear() const;
    int getUcsEnrolled() const;

    bool operator==(const Student& other) const;
};


#endif //AEDPROJECT_STUDENT_H
