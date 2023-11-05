//
// Created by vascocosta on 11/1/23.
//

#ifndef AEDPROJECT_TICKET_H
#define AEDPROJECT_TICKET_H

#include <iostream>
#include "Student.h"
#include "Lesson.h"

/**
 * @brief Represents a ticket for schedule changes.
 */

class Ticket {
private:
    /// The student associated with the ticket.
    Student student_;
    /// The UcClasses involved in the ticket.
    std::vector<UcClass> ucClasses_;
    /// The type of the ticket: 'a' for add, 'd' for delete, 's' for switch.
    char type_;

public:
    Ticket();

    /**
     * Constructor for a ticket to add or delete a UcClass.
     * @param student The student associated with the ticket.
     * @param type The type of the ticket ('a' for add, 'd' for delete).
     * @param ucClass The UcClass to be added or deleted.
     */
    Ticket(Student& student, const char& type, const UcClass& ucClass);

    /**
     * Constructor for a ticket to switch from one UcClass to another.
     * @param student The student associated with the ticket.
     * @param type The type of the ticket ('s' for switch).
     * @param from The UcClass to switch from.
     * @param to The UcClass to switch to.
     */
    Ticket(Student& student, const char& type, const UcClass& from, const UcClass& to);

    Student& getStudent();
    const std::vector<UcClass> getUcClasses() const;
    const char& getType() const;

};


#endif //AEDPROJECT_TICKET_H
