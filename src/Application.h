//
// Created by vascocosta on 10/28/23.
//

#ifndef AEDPROJECT_APPLICATION_H
#define AEDPROJECT_APPLICATION_H

#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include "UcClass.h"
#include "Schedule.h"
#include "Student.h"
#include "Ticket.h"

class Application {
private:
    std::vector<UcClass> ucClasses_;
    std::set<Student> students_;
    std::queue<Ticket> tickets_; // requests to process
    std::list<Ticket> processedTickets_; // to undo: if undo-ed should be eliminated from processed tickets, so podem ir tickets ACEITES
    std::map<UcClass, int> occupancy_; // ocupação por turma

public:
    Application();

    void readFiles(const std::string& file1, const std::string& file2, const std::string& file3);

    void schedules() const;
    void schedulesPerUc() const;
    void schedulesPerStudent() const;

    void students();
    void studentsListing();
    void studentsSearch();
    std::list<Student> studentsSort(bool ascending, bool (*comparator)(const Student& a, const Student& b));
    bool getOrderAndSize(bool& order, int& size) const;

    static bool compareStudentsByNameAscending(const Student& student1, const Student& student2);
    static bool compareStudentsByIdAscending(const Student& student1, const Student& student2);
    static bool compareStudentsByYearAscending(const Student& student1, const Student& student2);
    static bool compareStudentsByUcsAscending(const Student& student1, const Student& student2);

    void tickets();

    void ticketHandling();
    bool processTicket(Ticket& ticket);
    void undoTickets();
    bool classBalanceDisturbed(int numStudents, const UcClass &ucClassTo) const;
    bool checkOverlapping(const Student &student, const UcClass& ucClass) const;

    void ucInfo() const;
    void classInfo(const std::string& ucClass) const;

    void sysLog();

    int dayStrToInt(const std::string& day);
    bool ucClassExists(UcClass& ucClass) const; // passa por referencia ucclass para poder alterar
    bool studentExists(Student& student) const;

};


#endif //AEDPROJECT_APPLICATION_H
