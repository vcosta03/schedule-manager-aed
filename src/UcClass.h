//
// Created by vascocosta on 10/20/23.
//

#ifndef AEDPROJECT_UCCLASS_H
#define AEDPROJECT_UCCLASS_H

#include <string>
#include <list>


class UcClass {
private:
    std::string ucId_;
    std::string classId_;


public:
    UcClass();
    UcClass(std::string& ucId, std::string& classId);
    std::string getUcId() const;
    std::string getClassId() const;

};


#endif //AEDPROJECT_UCCLASS_H
