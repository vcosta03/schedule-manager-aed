//
// Created by vascocosta on 10/28/23.
//

#include "Application.h"
#include "UcClass.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>

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
//
//    for (auto& row : data2) {
//        bool studentFound = false;
//        Student currStudent(row[0], row[1]);
//        UcClass currUcClass(row[2], row[3]);
//
//        if (ucClassExists(currUcClass)) {
//            for (Student& student : students_) {
//                if (currStudent == student) {
//                    student.pushUcClass(currUcClass);
//                    studentFound = true;
//                    break;
//                }
//            }
//            if (!studentFound) {
//                currStudent.pushUcClass(currUcClass);
//                students_.push_back(currStudent);
//            }
//
//        }
//
//        else
//            std::cerr << "Invalid UC/Class code combination.\n";
//
//    }

    // TENTAR POR NUM SET INFORMACAO

    for (auto& row : data2) {
        Student currStudent(row[0], row[1]);
        UcClass currUcClass(row[2], row[3]);
        std::list<UcClass> ucClasses;

        auto it = studentsSet_.find(currStudent);

        if (ucClassExists(currUcClass)) {
            if (it != studentsSet_.end()) {
                ucClasses = it->getUcClasses();
                studentsSet_.erase(it);
            }

            currStudent.setUcClasses(ucClasses);
            currStudent.pushUcClass(currUcClass);
            studentsSet_.insert(currStudent);
        }

        else
            std::cerr << "Invalid UC/Class code combination.\n";

    }

//    for (const auto& s : studentsSet_) {
//        std::cout << s.getStudentName() << s.getStudentCode() << '\n';
//    }

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
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;

    }

}

void Application::schedulesPerUc() const {
    std::string ucCode, classCode;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\n----------------------------------------\n\n";
    std::cout << "Enter the UC code: ";
    std::cin >> ucCode;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter the Class code: ";
    std::cin >> classCode;
    UcClass currUcClass(ucCode, classCode);


    if (ucClassExists(currUcClass)) {
        auto a = currUcClass.getLessons();

//        if (a.empty())
//            std::cout << "empty" << '\n';

        Schedule currSchedule(currUcClass);
        currSchedule.printSchedule(0);
    }

    else
        std::cout << "Invalid UC/Class code combination.\n";
}

void Application::schedulesPerStudent() const {
    bool studentFound = false;
    std::string input;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\n----------------------------------------\n\n";
    std::cout << "Enter the Student's name or code: ";
    std::getline(std::cin,input);

    if (input.empty()) {
        std::cout << "Invalid input.\n";
        schedules();
        return;
    }

    if (input.at(0) >= '0' && input.at(0) <= '9') {
        for (const Student& student : studentsSet_) {
            if (student.getStudentCode() == input) {
                studentFound = true;

                Schedule currSchedule(student);
                currSchedule.printSchedule(1);
                break;
            }
        }
    }

    else {
        for (const Student& student : studentsSet_) {
            if (student.getStudentName() == input) {
                studentFound = true;

                std::cout << "\n----------------------------------------\n";
                std::cout << std::setw(20) << student.getStudentName() << "'s Schedule\n\n";
                Schedule currSchedule(student);
                currSchedule.printSchedule(1);
                break;
            }
        }

    }

    if (!studentFound){
        std::cout << "Student not found/doesn't exist.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        schedules();
    }
}

bool Application::ucClassExists(UcClass &ucClass) const {
    for (const auto& uc : ucClasses_) {
        if (uc == ucClass) {
            ucClass = uc;
            return true;
        }
    }
    return false;
}



const std::list<Student> &Application::getStudents() const {
    return students_;
}

void Application::students() {
    std::cout << "\n--------------Student Menu--------------\n\n"; //40 chars
    std::cout << "\t1. List students\n";
    std::cout << "\t2. Find a student\n";
    std::cout << "\n\t  Press q to exit current menu" << '\n';
    std::cout << "----------------------------------------\n\n";

    std::string option;

    std::cout << "> ";
    std::cin >> option;

    if (option.length() != 1) {
        std::cout << "Choose a valid option!\n";
        students();
        return;
    }

    switch (option[0]) {
        case '1':
            studentsListing();
            break;
        case '2': {
            studentsSearch();
            break;
        }
        case 'q':
            break;
        default:
            std::cout << "Choose a valid option!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;

    }

}

void Application::studentsListing() {
    std::string optionMenu;
    int size;
    bool ascending;
    std::list<Student> sortedStudents;
    std::set<Student,bool (*)(const Student& a, const Student& b)> sortedStudentsSet;



    std::cout << "\n-------------Student Listing------------\n\n"; //40 chars
    std::cout << "List by:\n";
    std::cout << "\t1. Name\n";
    std::cout << "\t2. ID\n";
    std::cout << "\t3. Academic Year\n";
    std::cout << "\t4. Number of UC's enrolled\n";
    std::cout << "\n\t  Press q to exit current menu" << '\n';
    std::cout << "----------------------------------------\n\n";

    std::cout << "> ";
    std::cin >> optionMenu;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (optionMenu.length() != 1 ) {
        std::cout << "Choose a valid option!\n";
        studentsListing();
        return;
    }

    if (optionMenu[0] == 'q') {
        return;
    }

    if (getOrderAndSize(ascending, size)) {
        switch (optionMenu[0]) {
            case '1':
                sortedStudents = studentsSort(ascending, compareStudentsByNameAscending);
                break;
            case '2':
                sortedStudents = studentsSort(ascending, compareStudentsByIdAscending);
                break;
            case'3':
                sortedStudents = studentsSort(ascending, compareStudentsByYearAscending);
                break;
            case '4':
                sortedStudents = studentsSort(ascending, compareStudentsByUcsAscending);
                break;
            default:
                std::cout << "Choose a valid menu option!\n";
                studentsListing();
                return;
        }
        std::cout << "\n----------------------------------------\n";
        std::cout << std::setw(11) << "ID |" << std::setw(20) << "Name |" << std::setw(7) << "Year |" << std::setw(7) << "UC's |" << '\n';

        size_t limit = (size == -1 ? sortedStudents.size()-1 : size), i = 0;
        auto it = sortedStudents.begin();

        while (i < limit && it != sortedStudents.end()){
            std::cout << std::setw(9) << it->getStudentCode() << " | "
                    << std::setw(17) << it->getStudentName() << " | "
                    << std::setw(4) << it->getCurricularYear() << " | "
                    << std::setw(4) << it->getUcsEnrolled() << " |" << '\n';

            it++;
            i++;
        }

    }

    else {
        studentsListing();
        return;
    }


}


void Application::studentsSearch() {
    std::string input;
    bool studentFound;
    Student currStudent;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\n----------------------------------------\n\n";
    std::cout << "Enter the Student's name or code: ";
    std::getline(std::cin, input);

    if (input.empty()) {
        std::cout << "Invalid input.\n";
        students();
        return;
    }

    std::set<Student>::const_iterator it;

    if (input.at(0) >= '0' && input.at(0) <= '9') {
        currStudent.setCode(input);
        it = studentsSet_.find(currStudent);
//        for (const Student& student : students_) {
//            if (student.getStudentCode() == input) {
//                studentFound = true;
//                currStudent = student;
//                break;
//            }
//        }
    }

    else {
        currStudent.setName(input);
        it = std::find_if(
                studentsSet_.begin(),
                studentsSet_.end(),
                [input](const Student& student) {
                    return student.getStudentName() == input;
                });
//        for (const Student& student : students_) {
//            if (student.getStudentName() == input) {
//                studentFound = true;
//                currStudent = student;
//                break;
//            }
//        }

    }



//    if (!studentFound){
//        std::cout << "Student not found/doesn't exist.\n";
//
//        std::cin.clear();
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//        students();
//        return;
//    }

    if (it == studentsSet_.end()) {
        std::cout << "Student not found/doesn't exist.\n";

        students();
        return;
    }

    else {
        currStudent = *it;
        std::cout << "\n----------------------------------------\n";
        std::cout << std::setw(20) << currStudent.getStudentName() << "'s Profile\n\n";
        std::cout << "Name: " << std::setw(34) << currStudent.getStudentName() << '\n';
        std::cout << "Code: " << std::setw(34) << currStudent.getStudentCode() << '\n';
        std::cout << "Year: " << std::setw(34) << currStudent.getCurricularYear() << '\n';
        std::cout << "UCs Enrolled:\n";

        for (const UcClass& uc : currStudent.getUcClasses()) {
            std::cout << std::setw(9) <<"UC: " << uc.getUcId() << " | " << "Class: " << uc.getClassId() <<'\n';
        }
    }

}


bool Application::compareStudentsByNameAscending(const Student& student1, const Student& student2) {
    return student1.getStudentName() < student2.getStudentName();
}

bool Application::compareStudentsByIdAscending(const Student& student1, const Student& student2) {
    return student1.getStudentCode() < student2.getStudentCode();
}

bool Application::compareStudentsByYearAscending(const Student& student1, const Student& student2) {
    return student1.getCurricularYear() < student2.getCurricularYear();
}

bool Application::compareStudentsByUcsAscending(const Student& student1, const Student& student2) {
    return student1.getUcsEnrolled() < student2.getUcsEnrolled();
}
//
//void Application::studentsSort(bool ascending, bool (*comparator)(const Student& a, const Student& b)) {
//    if (ascending)
//        students_.sort(comparator);
//    else {
//        students_.sort(comparator);
//        students_.reverse();
//    }
//}

std::list<Student> Application::studentsSort(bool ascending, bool (*comparator)(const Student& a, const Student& b)) {
    std::list<Student> sortedStudents(studentsSet_.begin(), studentsSet_.end());
    sortedStudents.sort(comparator);

    if (!ascending)
        sortedStudents.reverse();

    return sortedStudents;
}


bool Application::getOrderAndSize(bool& ascending, int& size) const {
    short optionOrder;
    std::string optionSize;

    std::cout << "\n----------------------------------------\n\n";
    std::cout << "Sort in ascending (1) or descending (2)\norder?\n" << "> ";
    std::cin >> optionOrder;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (optionOrder != 1 && optionOrder != 2) {
        std::cout << "Choose a valid option!\n";
        return false;
    }

    else if (optionOrder == 1) {
        ascending = true;
    }

    else if (optionOrder == 2) {
        ascending = false;
    }

    std::cout << "\nHow many students? (Press ENTER for every student)\n" << "> ";
    std::getline(std::cin, optionSize);

    if (!optionSize.empty()) {
        try {
            size = std::stoi(optionSize);

            if (size <= 0 || size > 100) {
                std::cout << "The number of students to display must\nbe between 1 to 100, press ENTER for\nevery student.\n";
                return false;
            }

            return true;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Choose a valid option!\n";
            return false;
        }
    }

    else {
        size = -1;
        return true;
    }

}






