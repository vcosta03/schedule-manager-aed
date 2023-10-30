//
// Created by vascocosta on 10/28/23.
//

#include "Application.h"
#include "UcClass.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

Application::Application() = default;


void Application::readFiles(std::string file1, std::string file2, std::string file3) {
    std::ifstream f1(file1); //should be classes_per_uc.csv
    std::ifstream f2(file2); //should be classes.csv
    std::ifstream f3(file3); //should be students_classes.csv

    std::vector<std::vector<std::string>> data1, data2;
    std::string line1, line2, line3;


    // ignore header
    std::getline(f1, line1);
    std::getline(f2, line2);
    std::getline(f3, line3);


    if (!f1.is_open() || !f2.is_open() || !f3.is_open()) {
        std::cerr << "Failed to open a CSV file." << std::endl;
    }


    while (getline(f1, line1)) {
        std::istringstream s1(line1);
        std::string ucCode, classCode;

        if (std::getline(s1, ucCode, ',') && std::getline(s1, classCode, '\r')) {
            ucClasses_.emplace_back(ucCode, classCode);
        }

        else
            std::cerr << "Invalid line1 in the CSV file: " << line1 << std::endl;
    }



    while (std::getline(f2, line2)) {
        std::vector<std::string> row;
        std::istringstream s2(line2.substr(0, line2.size() - 1));
        std::string item;

        while (std::getline(s2, item, ',')) {
            row.push_back(item);
        }

        data1.push_back(row);
    }

    for (auto& row : data1) {
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

    while (std::getline(f3, line3)) {
        std::vector<std::string> row;
        std::istringstream s3(line3.substr(0, line3.size() - 1));
        std::string item;

        while (std::getline(s3, item, ',')) {
            row.push_back(item);
        }

        data2.push_back(row);
    }

    for (auto& row : data2) {
        bool studentFound = false;
        Student currStudent(row[0], row[1]);
        UcClass currUcClass(row[2], row[3]);

        if (ucClassExists(currUcClass)) {
            for (Student& student : students_) {
                if (currStudent == student) {
                    student.pushUcClass(currUcClass);
                    studentFound = true;
                    break;
                }
            }
            if (!studentFound) {
                currStudent.pushUcClass(currUcClass);
                students_.push_back(currStudent);
            }

        }

        else
            std::cerr << "Invalid UC/Class code combination\n";

    }

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
            schedulesPerStudent();
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
        std::cout << "Invalid UC/Class code combination.\n";
}

void Application::schedulesPerStudent() const {
    bool studentFound = false;
    std::string input;

    std::cout << "\n----------------------------------------\n\n";
    std::cout << "Enter the Student's name or code: ";
    std::cin >> input;

    if (input.at(0) >= '0' && input.at(0) <= '9') {
        for (const Student& student : students_) {
            if (student.getStudentCode() == input) {
                studentFound = true;

                Schedule currSchedule(student);
                currSchedule.printSchedule(1);
                break;
            }
        }
    }

    else {
        for (const Student& student : students_) {
            if (student.getStudentName() == input) {
                studentFound = true;

                Schedule currSchedule(student);
                currSchedule.printSchedule(1);
                break;
            }
        }

    }

    if (!studentFound){
        std::cout << "Student not found/doesn't exist.\n";
        schedules();
    }
}

bool Application::ucClassExists(UcClass &ucClass) const {
    for (const auto& uc : ucClasses_) {
        if (uc == ucClass){
            ucClass = uc;
            return true;

        }
    }
    return false;
}



const std::list<Student> &Application::getStudents() const {
    return students_;
}

void Application::students() const {
    std::cout << "\n--------------Student Menu--------------\n\n"; //40 chars
    std::cout << "\t1. List students\n";
    std::cout << "\t2. Find a student\n";
    std::cout << "\n\t  Press q to exit current menu" << '\n';
    std::cout << "----------------------------------------\n\n";

    char option;

    std::cout << "> ";
    std::cin >> option;

    switch (option) {
        case '1':
//            studentsListing();
            break;
        case '2': {
            studentsSearch();
            break;
        }
        case 'q':
            break;
        default:
            std::cout << "Choose a valid option!\n";
            break;

    }

}

void Application::studentsListing() const {

}

void Application::studentsSearch() const {
    std::string input;
    bool studentFound;

    Student currStudent;

    std::cout << "\n----------------------------------------\n\n";
    std::cout << "Enter the Student's name or code: ";
    std::cin >> input;

    if (input.at(0) >= '0' && input.at(0) <= '9') {
        for (const Student& student : students_) {
            if (student.getStudentCode() == input) {
                studentFound = true;
                currStudent = student;
                break;
            }
        }
    }

    else {
        for (const Student& student : students_) {
            if (student.getStudentName() == input) {
                studentFound = true;
                currStudent = student;
                break;
            }
        }

    }

    if (!studentFound){
        std::cout << "Student not found/doesn't exist.\n";
        students();
    }

    else {
        std::cout << "\n----------------------------------------\n";
        std::cout << std::setw(18) << currStudent.getStudentName() << "'s Profile\n\n";
        std::cout << "Name: " << std::setw(34) << currStudent.getStudentName() << '\n';
        std::cout << "Code: " << std::setw(34) << currStudent.getStudentCode() << '\n';
        std::cout << "Year: " << std::setw(34) << currStudent.getCurricularYear() << '\n';
        std::cout << "UCs Enrolled:\n";

        for (const UcClass& uc : currStudent.getUcClasses()) {
            std::cout << std::setw(9) <<"UC: " << uc.getUcId() << " | " << "Class: " << uc.getClassId() <<'\n';
        }
    }

}




