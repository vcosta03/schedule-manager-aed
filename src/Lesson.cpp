//
// Created by vascocosta on 10/20/23.
//

#include <iostream>
#include <iomanip>
#include "Lesson.h"


Lesson::Lesson() = default;

Lesson::Lesson(int weekday, float startTime, float duration, std::string lessonType) {
    weekday_ = weekday;
    lessonType_ = lessonType;

    int hours = (int)startTime;
    startTime_ = hours * 100 + int(60 * float(startTime-(float)hours));
    duration_ = int(60 * duration);
}


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

bool Lesson::areOverlapping(const Lesson& lesson) const{
    /* Futuramente, podemos analisar por dia, assim eliminamos uma condição  */
    if ((lessonType_ == "T" || lesson.getLessonType() == "T") && (weekday_ != lesson.getWeekday() || weekday_ == lesson.getWeekday() && (startTime_+duration_ < lesson.getStartTime() || startTime_ > lesson.getStartTime()+lesson.getDuration())))
        return false;
    return true;
}

int Lesson::getEndTime() const {
    int duration = duration_;
    int hours = 0;

    while (duration >= 60) {
        duration -= 60;
        hours++;
    }

    int res = startTime_ + (100 * hours);

    if (res%100 + duration >= 60){
        res += 100 - res%100 + (duration - (60 - res%100)); // Primeiro adiciona minutos suficientes até +1 hora e dps adiciona minutos q sobram 
    }

    else
        res += duration;

    return res;
}

std::string Lesson::printTime() const {
    std::string initial = std::to_string(startTime_/100) + ':' + (startTime_%100 < 10 ? '0' + std::to_string(startTime_%100) : std::to_string(startTime_%100));
    std::string end = std::to_string(getEndTime()/100) + ':' + (getEndTime()%100 < 10 ? '0' + std::to_string(getEndTime()%100) : std::to_string(getEndTime()%100));

    return initial + '-' + end ;
}

