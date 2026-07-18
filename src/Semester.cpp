#include "Semester.hpp"
#include <string>
#include <vector>
#include <numeric>

// Constructor
Semester::Semester(const std::string& code) : semesterCode(code) {}

// Getters
std::string Semester::getSemesterCode() const { 
    return semesterCode; 
}

const std::vector<Course>& Semester::getCourses() const { 
    return courses;
}

// Setters
void Semester::setSemesterCode(const std::string& code) { 
    semesterCode = code;
}

// Add a course to our dynamic vector collection
void Semester::addCourse(const Course& course) {
    courses.push_back(course);
}

// Compute the Credit-Weighted GPA
double Semester::calculateGPA() const {
    // Edge case validation: prevent division by zero if semester is empty
    if (courses.empty()) {
        return 0.0;
    }

    double totalGradePoints = 0.0;
    int totalCredits = 0;

    // Loop through each course to aggregate weighted values
    for (const auto& course : courses) {
        totalGradePoints += (course.getGradePoints() * course.getCredits());
        totalCredits += course.getCredits();
    }

    // Defensive check: if courses exist but all have 0 credits
    if (totalCredits == 0) {
        return 0.0;
    }

    // Calculate final weighted average
    return totalGradePoints / totalCredits;
}
