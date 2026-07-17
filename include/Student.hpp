#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>
#include "Semester.hpp"

class Student {
private:
    std::string firstName;
    std::string lastName;
    std::vector<Semester> semesters;

public:
    // Constructor (const references for efficiency)
    Student(const std::string& fName, const std::string& lName);

    // Getters (const for safety)
    std::string getFirstName() const;
    std::string getLastName() const;
    const std::vector<Semester>& getSemesters() const; // Returns reference to semesters

    // Setters
    void setFirstName(const std::string& fName);
    void setLastName(const std::string& lName);

    //Logic Methods
    void addSemester(const Semester& semester);
    double calculateCGPA() const; // Iterates through semesters to compute CGPA
};

#endif // STUDENT_HPP
