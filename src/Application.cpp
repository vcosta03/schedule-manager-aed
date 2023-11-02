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

#define CAP 30 // cap para estudantes por turma

Application::Application() = default;


void Application::readFiles(const std::string& file1, const std::string& file2, const std::string& file3) {
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
            UcClass uc(ucCode, classCode);
            ucClasses_.emplace_back(ucCode, classCode);
            occupancy_[uc] = 0;
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
        Student currStudent(row[0], row[1]);
        UcClass currUcClass(row[2], row[3]);
        std::list<UcClass> ucClasses;

        auto it = students_.find(currStudent);

        if (ucClassExists(currUcClass)) {
            if (it != students_.end()) {
                ucClasses = it->getUcClasses();
                students_.erase(it);
            }

            currStudent.setUcClasses(ucClasses);
            currStudent.pushUcClass(currUcClass);
            students_.insert(currStudent);

            occupancy_[currUcClass]++;
        }

        else
            std::cerr << "Invalid UC/Class code combination.\n";

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

    std::string option;

    std::cout << "> ";
    std::cin >> option;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (option.length() != 1) {
        std::cout << "Choose a valid option!\n";
        schedules();
        return;
    }

    switch (option[0]) {
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
            schedules();
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

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    UcClass currUcClass(ucCode, classCode);


    if (ucClassExists(currUcClass)) {
        auto a = currUcClass.getLessons();

        Schedule currSchedule(currUcClass);
        currSchedule.printSchedule(0);
    }

    else
        std::cout << "Invalid UC/Class code combination.\n";
}

void Application::schedulesPerStudent() const {
    std::string input;
    Student currStudent;


    std::cout << "\n----------------------------------------\n\n";
    std::cout << "Enter the Student's name or code: ";
    std::getline(std::cin,input);

    if (input.empty()) {
        std::cout << "Invalid input.\n";
        schedules();
        return;
    }

    if (input.at(0) >= '0' && input.at(0) <= '9')
        currStudent.setCode(input);


    else
        currStudent.setName(input);

    if (studentExists(currStudent)) {
        std::cout << "\n----------------------------------------\n";
        std::cout << std::setw(20) << currStudent.getStudentName() << "'s Schedule\n\n";
        Schedule currSchedule(currStudent);
        currSchedule.printSchedule(1);
    }

    else {
        std::cout << "Student not found/doesn't exist.\n";
        schedules();
        return;
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

    if (input.at(0) >= '0' && input.at(0) <= '9') {
        currStudent.setCode(input);

    }

    else {
        currStudent.setName(input);
    }

    if (studentExists(currStudent)) {
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

    else {
        std::cout << "Student not found/doesn't exist.\n";
        students();
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

std::list<Student> Application::studentsSort(bool ascending, bool (*comparator)(const Student& a, const Student& b)) {
    std::list<Student> sortedStudents(students_.begin(), students_.end());
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

const std::set<Student> &Application::getStudents() const {
    return students_;
}

void Application::tickets() {
    std::string inputStudent, option;
    Student currStudent;

    std::cout << "\n----------------------------------------\n\n";
    std::cout << "Enter the Student's name or code: ";
    std::getline(std::cin, inputStudent);

    if (inputStudent.empty()) {
        std::cout << "Invalid input.\n";
        tickets();
        return;
    }

    if (inputStudent.at(0) >= '0' && inputStudent.at(0) <= '9') {
        currStudent.setCode(inputStudent);

    }

    else {
        currStudent.setName(inputStudent);
    }

    if (studentExists(currStudent)) {
        std::cout << "\n--------------Tickets Menu--------------\n\n"; //40 chars
        std::cout << "Student: " << currStudent.getStudentName() << "\n\n";
        std::cout << "\t1. Enroll in a new UC\n";
        std::cout << "\t2. Withdraw from an UC\n";
        std::cout << "\t3. Switch classes within an UC\n";
        std::cout << "\t4. Switch UC\n";
        std::cout << "\n\t  Press q to exit current menu" << '\n';
        std::cout << "----------------------------------------\n\n";

        std::cout << "> ";
        std::cin >> option;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (option.length() != 1) {
            std::cout << "Choose a valid option!\n";
            tickets();
            return;
        }

        switch (option[0]) {
            case '1': {
                std::string inputUc, inputClass;

                std::cout << "\n----------------------------------------\n\n";
                std::cout << "Enter the UC code: ";
                std::cin >> inputUc;

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                for (const UcClass& uc : currStudent.getUcClasses()) {
                    if (uc.getUcId() == inputUc) {
                        std::cout << '\n' << currStudent.getStudentName() << " is already in " << uc.getUcId() << ".\n";
                        return;
                    }
                }

                std::cout << "Enter the Class code: ";
                std::cin >> inputClass;

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                UcClass currUcClass(inputUc,  inputClass);

                if (!ucClassExists(currUcClass)) {
                    std::cout << "Invalid UC/Class code combination.\n";
                    return;
                }

                Ticket currTicket(currStudent, 'a', currUcClass);
                tickets_.push(currTicket);

                std::cout << "\nThe following ticket has been added to\nthe queue and is waiting for approval:\n\n";
                std::cout << "-> Enroll " << currStudent.getStudentName() << " in " << currUcClass.getUcId() << " in the class " << currUcClass.getClassId() << ".\n";

                break;
            }

            case '2': {
                std::string inputUc, inputClass;
                UcClass currUcClass;

                std::cout << "\n----------------------------------------\n\n";
                std::cout << "Enter the UC code: ";
                std::cin >> inputUc;

                for (const UcClass& uc : currStudent.getUcClasses()) {
                    if (uc.getUcId() == inputUc) {
                        currUcClass = uc;
                        break;
                    }
                }

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (currUcClass.getClassId().empty() || currUcClass.getUcId().empty()) {
                    std::cout << '\n' << currStudent.getStudentName() << " is not enrolled in "<< inputUc << '\n';
                    return;
                }

                Ticket currTicket(currStudent, 'd', currUcClass);
                tickets_.push(currTicket);

                std::cout << "\nThe following ticket has been added to\nthe queue and is waiting for approval:\n\n";
                std::cout << "-> Withdraw " << currStudent.getStudentName() << " from " << currUcClass.getUcId() << ", class " << currUcClass.getClassId() << ".\n";


                break;
            }

            case '3': {
                std::string inputUc, inputClass;
                UcClass ucClassRemove;

                std::cout << "\n----------------------------------------\n\n";
                std::cout << "Enter the UC code: ";
                std::cin >> inputUc;

                for (const UcClass& uc : currStudent.getUcClasses()) {
                    if (uc.getUcId() == inputUc) {
                        ucClassRemove = uc;
                        break;
                    }
                }

                if (ucClassRemove.getClassId().empty() || ucClassRemove.getUcId().empty()) {
                    std::cout << '\n' << currStudent.getStudentName() << " is not enrolled in "<< inputUc << '\n';
                    return;
                }

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Enter the Class code you desire: ";
                std::cin >> inputClass;

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                UcClass ucClassAdd(inputUc,  inputClass);

                if (!ucClassExists(ucClassAdd)) {
                    std::cout << "Invalid UC/Class code combination.\n";
                    return;
                }

                Ticket currTicket(currStudent, 's', ucClassRemove, ucClassAdd);
                tickets_.push(currTicket);

                std::cout << "\nThe following ticket has been added to\nthe queue and is waiting for approval:\n\n";
                std::cout << "-> Switch " << currStudent.getStudentName() << " from class " << ucClassRemove.getClassId()
                            << " to " << ucClassAdd.getClassId() << ",\nwithin " << ucClassAdd.getUcId() << ".\n";


                break;
            }

            case '4': {
                std::string inputUcRemove, inputUcAdd, inputClassAdd;
                UcClass ucClassRemove;


                std::cout << "\n----------------------------------------\n\n";
                std::cout << "Enter the UC code to withdraw: ";
                std::cin >> inputUcRemove;
                std::cout << '\n';

                for (const UcClass& uc : currStudent.getUcClasses()) {
                    if (uc.getUcId() == inputUcRemove) {
                        ucClassRemove = uc;
                        break;
                    }
                }

                if (ucClassRemove.getClassId().empty() || ucClassRemove.getUcId().empty()) {
                    std::cout << currStudent.getStudentName() << " is not enrolled in "<< inputUcRemove << '\n';
                    return;
                }

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Enter the desired UC code: ";
                std::cin >> inputUcAdd;

                std::cout << "Enter the desired Class code: ";
                std::cin >> inputClassAdd;

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                UcClass ucClassAdd(inputUcAdd, inputClassAdd);

                if (!ucClassExists(ucClassAdd)) {
                    std::cout << "Invalid UC/Class code combination.\n";
                    return;
                }

                Ticket currTicket(currStudent, 's', ucClassRemove, ucClassAdd);
                tickets_.push(currTicket);

                std::cout << "\nThe following ticket has been added to\nthe queue and is waiting for approval:\n\n";
                std::cout << "-> Switch " << currStudent.getStudentName() << " from UC: " << ucClassRemove.getUcId() << " | Class: "<< ucClassRemove.getClassId()
                            <<"\nto UC: " << ucClassAdd.getUcId() << " | Class: " << ucClassAdd.getClassId() <<".\n";

                break;
            }

            case 'q':
                break;
            default:
                std::cout << "Choose a valid option!\n";
                return;
        }
    }

    else {
        std::cout << "Student not found/doesn't exist.\n";
    }
}

bool Application::studentExists(Student &student) const {
    std::set<Student>::const_iterator it;

    if (student.getStudentName().empty()) {
        it = students_.find(student);
    }

    else {
        std::string name = student.getStudentName();
        it = std::find_if(
                students_.begin(),
                students_.end(),
                [name](const Student& student) {
                    return student.getStudentName() == name;
                });
    }

    if (it == students_.end()) {
        return false;
    }

    student = *it;
    return true;

}



void Application::ticketHandling() {
    std::string option;

    std::cout << "\n-----------Ticket Management-----------\n\n"; //40 chars
    std::cout << "\t1. Check tickets in queue\n";
    std::cout << "\t2. Accept every ticket\n";
    std::cout << "\t3. Accept next ticket in queue\n";
    std::cout << "\t4. Reject every ticket\n";
    std::cout << "\t5. Reject next ticket in queue\n";
    std::cout << "\t6. Undo a ticket\n";
    std::cout << "\n\t  Press q to exit current menu" << '\n';
    std::cout << "----------------------------------------\n\n";

    std::cout << "> ";
    std::cin >> option;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (option.length() != 1) {
        std::cout << "Choose a valid option!\n";
        ticketHandling();
        return;
    }

    switch (option[0]) {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        case 'q':
            break;
        default:
            std::cout << "Choose a valid option!\n";
            ticketHandling();
            return;
    }
}


int Application::occupationPerClass(const UcClass &ucClass) const {
    int studentsRegistered = 0;

    for (const Student& student : students_) {
        for (const UcClass& studentUc : student.getUcClasses()) {
            if (studentUc == ucClass) {
                studentsRegistered++;
                break;
            }
        }
    }

    return studentsRegistered;
}

void Application::ucInfo() const {
    std::string displayUc, inputUcCode, optionMenu;

    bool ucFound = false;

    int i = 0;

    std::cout << "\n-------------Available UCs--------------\n\n\t";

    for (const UcClass& uc : ucClasses_) {
        if (uc.getUcId() != displayUc) {
            displayUc = uc.getUcId();
            std::cout << displayUc;

            i++;
            if (i % 3 == 0)
                std::cout << '\n' << '\t';
            else
                std::cout << '\t';
        }

    }

    std::cout << "\n\n----------------------------------------\n\n";
    std::cout << "Enter the UC code: ";
    std::cin >> inputUcCode;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (const UcClass& uc : ucClasses_) {
        if (inputUcCode == uc.getUcId()) {
            ucFound = true;
        }
    }

    if (!ucFound) {
        std::cout << "UC not found/doesn't exist.\n";
        return;
    }

    std::cout << "\n----------" << inputUcCode <<" Information----------\n\n"; //40 chars
    std::cout << "\t1. Classes\n";
    std::cout << "\t2. Occupancy\n";
    std::cout << "\t3. Registered students\n";
    std::cout << "\n\t  Press q to exit current menu" << '\n';
    std::cout << "----------------------------------------\n\n";

    std::cout << "> ";
    std::cin >> optionMenu;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (optionMenu.length() != 1) {
        std::cout << "Choose a valid option!\n";
        return;
    }

    switch (optionMenu[0]) {
        case '1': {
            classInfo(inputUcCode);
            break;
        }
        case '2': {
            int occ = 0;
            int numClasses = 0;

            for (const auto& p : occupancy_) {
                if (p.first.getUcId() == inputUcCode) {
                    occ += p.second;
                    numClasses++;
                }
            }

            int maxOcc = CAP * numClasses;
            float occPercent = ((float)occ / maxOcc) * 100.0;


            std::cout << "\n----------------------------------------\n";
            std::cout << "UC: " << inputUcCode << "\n\n";
            std::cout << "Occupancy:" << std::setw(30) <<  occ << '\n';
            std::cout << "Vacancies:" << std::setw(30) << maxOcc - occ << "\n\n";

            std::cout << "\t\t";

            if (occPercent < 10 && occPercent > 0) {
                std::cout << "█░░░░░░░░░░░░░░░░░░░ " << (int)occPercent << "%\n";
                break;
            }

            for (int i = 0; i < (int)(occPercent/10.0); i++) {
                std::cout << "██";
            }

            for (int i = 0; i < 10 - (int)(occPercent/10.0); i++) {
                std::cout <<"░░";
            }

            std::cout << ' ' << (int)occPercent << "%\n";

            break;
        }
        case '3': {
            std::cout << "\n-----------Registered Students----------\n";
            std::cout << "UC: " << inputUcCode << "\n\n";
            std::cout << std::setw(13) << "ID |" << std::setw(20) << "Name |" << std::setw(7) << "Year |" << '\n';

            for (const Student& student : students_){
                for (const UcClass& uc : student.getUcClasses()) {
                    if (uc.getUcId() == inputUcCode) {
                        std::cout << std::setw(11) << student.getStudentCode() << " |"
                                  << std::setw(18) << student.getStudentName() << " |"
                                  << std::setw(5) << student.getCurricularYear() << " |\n";
                    }
                }
            }
            break;
        }
        case 'q':
            break;
        default:
            std::cout << "Choose a valid option!\n";
            break;

    }

}

void Application::classInfo(const std::string& ucCode) const {
    std::string inputClassCode, optionMenu;


    std::cout << "\n-----------Available Classes------------\n\n\t";

    int i = 0;
    for (const UcClass& uc : ucClasses_) {
        if (uc.getUcId() == ucCode) {
            std::cout << uc.getClassId();
            i++;
            if (i % 3 == 0)
                std::cout << '\n' << '\t';
            else
                std::cout << "\t\t";
        }
    }

    std::cout << "\n\n----------------------------------------\n\n";
    std::cout << "Enter the Class code: ";
    std::cin >> inputClassCode;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    UcClass currUcClass(ucCode, inputClassCode);

    if (!ucClassExists(currUcClass)){
        std::cout << "Class not found/doesn't exist.\n";
        return;
    }

    std::cout << "\n------------" << currUcClass.getClassId() << " Information-----------\n\n"; //40 chars
    std::cout << "\t1. Occupancy\n";
    std::cout << "\t2. Registered students\n";
    std::cout << "\n\t  Press q to exit current menu" << '\n';
    std::cout << "----------------------------------------\n\n";


    std::cout << "> ";
    std::cin >> optionMenu;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (optionMenu.length() != 1) {
        std::cout << "Choose a valid option!\n";
        return;
    }

    switch (optionMenu[0]) {
        case '1': {
            auto pair = occupancy_.find(currUcClass);
            float occPercent = ((float)pair->second / CAP) * 100.0;

            std::cout << "\n----------------------------------------\n";
            std::cout << "UC: " << ucCode << " | " << "Class: " << inputClassCode << "\n\n";
            std::cout << "Occupancy:" << std::setw(30) <<  pair->second << '\n';
            std::cout << "Vacancies:" << std::setw(30) << CAP - pair->second << "\n\n";

            std::cout << "\t\t";

            if (occPercent < 10 && occPercent > 0) {
                std::cout << "█░░░░░░░░░░░░░░░░░░░ " << (int)occPercent << "%\n";
                break;
            }

            for (int i = 0; i < (int)(occPercent/10.0); i++) {
                std::cout << "██";
            }

            for (int i = 0; i < 10 - (int)(occPercent/10.0); i++) {
                std::cout <<"░░";
            }

            std::cout << ' ' << (int)occPercent << "%\n";

            break;
        }
        case '2': {
            std::cout << "\n-----------Registered Students----------\n";
            std::cout << "UC: " << ucCode << " | " << "Class: " << inputClassCode << "\n\n";
            std::cout << std::setw(13) << "ID |" << std::setw(20) << "Name |" << std::setw(7) << "Year |" << '\n';

            for (const Student& student : students_){
                for (const UcClass& uc : student.getUcClasses()) {
                    if (uc == currUcClass) {
                        std::cout << std::setw(11) << student.getStudentCode() << " |"
                                << std::setw(18) << student.getStudentName() << " |"
                                << std::setw(5) << student.getCurricularYear() << " |\n";
                    }
                }
            }

            break;
        }
        case 'q':
            break;

        default:
            std::cout << "Choose a valid option!\n";
            break;

    }

}









