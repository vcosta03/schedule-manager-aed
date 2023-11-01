//
// Created by vascocosta on 10/28/23.
//

#ifndef AEDPROJECT_APPLICATION_H
#define AEDPROJECT_APPLICATION_H

#include <iostream>
#include <map>
#include <map>
#include <set>
#include "UcClass.h"
#include "Schedule.h"
#include "Student.h"

class Application {
private:
    std::vector<UcClass> ucClasses_;
    std::list<Student> students_;
    std::set<Student> studentsSet_;

public:
    Application();

    const std::vector<UcClass> &getUcClasses() const;
    const std::list<Student> &getStudents() const;

    void readFiles(std::string file1, std::string file2, std::string file3);

    void schedules() const;
    void schedulesPerUc() const;
    void schedulesPerStudent() const;

    void students();
    void studentsListing();
    void studentsSearch();
    std::list<Student> studentsSort(bool ascending, bool (*comparator)(const Student& a, const Student& b));
    bool getOrderAndSize(bool& order, int& size) const;

    static bool compareStudentsByNameAscending(const Student& student1, const Student& student2);
    static bool compareStudentsByIdAscending(const Student& student1, const Student& student2);
    static bool compareStudentsByYearAscending(const Student& student1, const Student& student2);
    static bool compareStudentsByUcsAscending(const Student& student1, const Student& student2);



    int dayStrToInt(const std::string& day);
    bool ucClassExists(UcClass& ucClass) const;

};


#endif //AEDPROJECT_APPLICATION_H
