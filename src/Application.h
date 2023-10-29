//
// Created by vascocosta on 10/28/23.
//

#ifndef AEDPROJECT_APPLICATION_H
#define AEDPROJECT_APPLICATION_H

#include <iostream>
#include <set>
#include <map>
#include "UcClass.h"
#include "Schedule.h"

class Application {
private:
    std::vector<UcClass> ucClasses_;
    std::list<Schedule> schedules_;


public:
    Application();
    const std::vector<UcClass> &getUcClasses() const;
    const std::list<Schedule> &getSchedules() const;

    void schedules() const;
    void readFiles(std::string file1, std::string file2);
    int dayStrToInt(const std::string& day);
    void schedulesPerUc() const;
    bool ucClassExists(UcClass& ucClass) const;

};


#endif //AEDPROJECT_APPLICATION_H
