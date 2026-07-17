#ifndef SEMESTER_HPP
#define SEMESTER_HPP

#include <string>
#include <vector>
#include "Course.hpp"

class Semester {
private:
    std::string semesterCode;
    std::vector<Course> courses; 

public:
    // Constructor
    Semester(const std::string& code);

    // Getters
    std::string getSemesterCode() const;
    const std::vector<Course>& getCourses() const; 

    // Setters
    void setSemesterCode(const std::string& code);

    // Logic Methods
    void addCourse(const Course& course);
    double calculateGPA() const;

#endif // SEMESTER_HPP
