//
// Created by vascocosta on 10/20/23.
//

#ifndef AEDPROJECT_UCCLASS_H
#define AEDPROJECT_UCCLASS_H

#include <string>
#include <list>
#include <vector>
#include "Lesson.h"

/**
 * @brief Represents a pair of an UC and a Class.
 */

class UcClass {
private:
    std::string ucId_;
    std::string classId_;
    std::vector<Lesson> lessons_;

public:

    UcClass();
    UcClass(const std::string& ucId, const std::string& classId);

    const std::string &getUcId() const;
    const std::string &getClassId() const;
    std::vector<Lesson> getLessons() const;

    void pushLesson(const Lesson& lesson);

    bool operator==(const UcClass& other) const;
    bool operator<(const UcClass& other) const;

};


#endif //AEDPROJECT_UCCLASS_H
