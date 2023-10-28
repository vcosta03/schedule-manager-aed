//
// Created by vascocosta on 10/20/23.
//

#ifndef AEDPROJECT_LESSON_H
#define AEDPROJECT_LESSON_H

#include <string>

class Lesson {
private:
    int weekday_;
    int startTime_;
    int duration_;
    std::string lessonType_;
public:
    Lesson();
    Lesson(int weekday, int startTime, int duration, std::string lessonType) : weekday_(weekday), startTime_(startTime), duration_(duration), lessonType_(lessonType) {}
    int getWeekday() const;
    int getStartTime() const;
    int getDuration() const;
    int getEndTime() const;
    std::string printTime() const;
    std::string getLessonType() const;
    bool areOverlapping(Lesson& lesson);
};


#endif //AEDPROJECT_LESSON_H
