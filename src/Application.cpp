//
// Created by vascocosta on 10/28/23.
//

#include "Application.h"
#include "UcClass.h"
#include <fstream>
#include <sstream>
#include <algorithm>

Application::Application() = default;


void Application::readFiles(std::string file1, std::string file2) {
    std::ifstream f1(file1); //should be classes_per_uc.csv


    if (!f1.is_open()) {
        std::cerr << "Failed to open a CSV file." << std::endl;
    }

    std::string line;
    std::getline(f1, line); // ignore header

    while (getline(f1, line)) {
        std::istringstream s1(line);
        std::string ucCode, classCode;

        if (std::getline(s1, ucCode, ',') && std::getline(s1, classCode, '\r')) {
            ucClasses_.emplace_back(ucCode, classCode);
        }

        else
            std::cerr << "Invalid line in the CSV file: " << line << std::endl;
    }


//    std::string a = "L.EIC002";
//
//    for (UcClass& uc : ucClasses_) {
//        std::cout << uc.getUcId() << ' ' << uc.getClassId() << ' ' << (uc.getUcId() == a) << '\n';
//    }

    std::ifstream f2(file2); //should be classes.csv
    std::vector<std::vector<std::string>> data;
    std::string line2;

    std::getline(f2, line2);

    while (std::getline(f2, line2)) {
        std::vector<std::string> row;
        std::istringstream iss(line2.substr(0, line2.size() - 1));
        std::string item;

        while (std::getline(iss, item, ',')) {
            row.push_back(item);
        }

        data.push_back(row);
    }

    for (auto& row : data) {
        int weekday = dayStrToInt(row[2]);
        float startHour = std::stof(row[3]);
        float duration = std::stof(row[4]);
        std::string type = row[5];

        Lesson currLesson(weekday, startHour, duration, type);

        for (UcClass& uc : ucClasses_) {
            if (row[0] == uc.getClassId() && row[1] == uc.getUcId()) {
                uc.pushLesson(currLesson);
            }
        }
    }

    f2.close();

}


int Application::dayStrToInt(const std::string &day) {
    const std::map<std::string, int> dayNameMap = {
            {"Monday", 0},
            {"Tuesday", 1},
            {"Wednesday", 2},
            {"Thursday", 3},
            {"Friday", 4}
    };

    auto it = dayNameMap.find(day);
    if (it != dayNameMap.end()) {
        return it->second;
    }

    return -1;
}

const std::vector<UcClass> &Application::getUcClasses() const {
    return ucClasses_;
}

const std::list<Schedule> &Application::getSchedules() const {
    return schedules_;
}

void Application::schedules() const {
    std::cout << "\n-------------Schedule Menu--------------\n\n"; //40 chars
    std::cout << "\t1. Student\n";
    std::cout << "\t2. Class\n";
    std::cout << "\n\t  Press q to exit current menu" << '\n';
    std::cout << "----------------------------------------\n\n";

    char option;

    std::cout << "> ";
    std::cin >> option;

    switch (option) {
        case '1':
            option = 'q';
            break;
        case '2': {
            schedulesPerUc();
            break;
        }
        case 'q':
            break;
        default:
            std::cout << "Choose a valid option!\n";
            break;

    }

}

void Application::schedulesPerUc() const {
    std::string ucCode, classCode;

    std::cout << "\n----------------------------------------\n\n";
    std::cout << "Enter the UC code: ";
    std::cin >> ucCode;
    std::cout << "Enter the Class code: ";
    std::cin >> classCode;

    UcClass currUcClass(ucCode, classCode);


    if (ucClassExists(currUcClass)) {
        auto a = currUcClass.getLessons();

        if (a.empty())
            std::cout << "empty" << '\n';

        Schedule currSchedule(currUcClass);
        currSchedule.printSchedule(0);
    }

    else
        std::cout << "Invalid UC/Class code combination.";
}

bool Application::ucClassExists(UcClass &ucClass) const {
    for (const auto uc : ucClasses_) {
        if (uc == ucClass){
            ucClass = uc;
            return true;

        }
    }
    return false;
}




