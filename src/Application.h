//
// Created by vascocosta on 10/28/23.
//

#ifndef AEDPROJECT_APPLICATION_H
#define AEDPROJECT_APPLICATION_H

#include <iostream>
#include <map>
#include <set>
#include <queue>
#include "UcClass.h"
#include "Schedule.h"
#include "Student.h"
#include "Ticket.h"

/**
 *
 * @brief Core program class for data management and user interaction.
 *
 * This is the core class of the program, responsible for managing various data structures and functionalities.
 * It facilitates user interaction through submenus, enabling data manipulation, as well as reading and writing data
 * to CSV files.
 */

class Application {
private:
    /// Every UcClass in LEIC
    std::vector<UcClass> ucClasses_;
    /// Registered students in LEIC
    std::set<Student> students_;
    /// Tickets to be processed
    std::queue<Ticket> tickets_;
    /// Tickets that have been processed and can be reversed.
    std::list<Ticket> processedTickets_;
    /// Occupancy per UcClass
    std::map<UcClass, int> occupancy_;

public:
    /// Default constructor
    Application();

    /// Reads and parses data provided in the CSV's.
    void readFiles(const std::string& file1, const std::string& file2, const std::string& file3, const std::string& file4, const std::string& file5);
    /// Writes the system changes to a CSV.
    void writeLog(const std::string& file1);
    /// Writes the tickets yet to be processed data to a CSV.
    void writeTickets(const std::string file);

    /// Displays the Schedule menu and directs the program flow to submenus.
    void schedules() const;
    /// Displays the schedule for a specific UcClass.
    void schedulesPerUc() const;
    /// Displays the schedule for a specific Student.
    void schedulesPerStudent() const;

    /// Displays the Student menu and directs the program flow to submenus.
    void students();
    /// Lists and sorts the students, allowing different sorting option.
    void studentsListing();
    /// Searches a specific student.
    void studentsSearch();

    std::list<Student> studentsSort(bool ascending, bool (*comparator)(const Student& a, const Student& b));
    /// Retrieves user input for sorting order and the number of students to display, ensuring data validity.
    bool getOrderAndSize(bool& order, int& size) const;

    /// Compares two students by name in ascending order.
    static bool compareStudentsByNameAscending(const Student& student1, const Student& student2);
    /// Compares two students by id in ascending order.
    static bool compareStudentsByIdAscending(const Student& student1, const Student& student2);
    /// Compares two students by curricular year in ascending order.
    static bool compareStudentsByYearAscending(const Student& student1, const Student& student2);
    /// Compares two students by number of UC's in ascending order.
    static bool compareStudentsByUcsAscending(const Student& student1, const Student& student2);

    /// Displays ticket menu and allows users to create tickets related to schedule changes.
    void tickets();

    /// Displays ticket management menu and is responsible for managing new and processed tickets.
    void ticketHandling();
    /// Processes student tickets for enrollment, withdrawal, and class switching.
    bool processTicket(Ticket& ticket);
    /// Enables processed tickets to be reversed.
    void undoTickets();
    /// Checks class balance for potential disturbance when altering student count in a class.
    bool classBalanceDisturbed(int numStudents, const UcClass &ucClassTo) const;

    bool checkOverlapping(const Student &student, const UcClass& ucClass) const;

    /// Displays and manages information for a specific UC.
    void ucInfo() const;
    /// Displays and manages information for a specific Class.
    void classInfo(const std::string& ucClass) const;

    /// Displays the changes made to the system.
    void sysLog();

    /// Converts a day string to an integer (0-4) for schedule management.
    int dayStrToInt(const std::string& day);
    /// Checks if a UcClass exists and if so updates the value.
    bool ucClassExists(UcClass& ucClass) const;
    /// Checks if a student exists and if so updates the value.
    bool studentExists(Student& student) const;

};


#endif //AEDPROJECT_APPLICATION_H
