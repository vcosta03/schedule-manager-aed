//
// Created by vascocosta on 10/20/23.
//

#include <iostream>
#include "Lesson.h"


Lesson::Lesson() = default;


int Lesson::getWeekday() const {
    return weekday_;
}

int Lesson::getStartTime() const {
    return startTime_;
}

int Lesson::getDuration() const {
    return duration_;
}

std::string Lesson::getLessonType() const {
    return lessonType_;
}

bool Lesson::areOverlapping(Lesson& lesson) {
    if ((lessonType_ == "T" || lesson.getLessonType() == "T") && (weekday_ != lesson.getWeekday() || weekday_ == lesson.getWeekday() && (startTime_+duration_ < lesson.getStartTime() || startTime_ > lesson.getStartTime()+lesson.getDuration())))
        return false;
    return true;
}

int Lesson::getEndTime() const {
    int duration = duration_;
    int hours = 0;

    while (duration > 60) {
        duration -= 60;
        hours++;
    }

    int res = startTime_ + (100 * hours);

    if (res%100 + duration > 60){
        res += 100 - res%100 + (duration - (60 - res%100)); // Primeiro adiciona minutos suficientes até +1 hora e dps adiciona minutos q sobram 
    }

    return res;
}
