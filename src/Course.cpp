#include "Course.hpp"
#include <string>

// anonymous namespace keeps this table private to this file
namespace {
    struct GradeMapping {
        double minScore;
        const char* letter;
        double points;
    };

    const GradeMapping GRADE_TABLE[] = {
        {90.0, "A", 4.0},
        {80.0, "B", 3.0},
        {70.0, "C", 2.0},
        {60.0, "D", 1.0},
        {0.0,  "F", 0.0}
    };
}

// Constructor Implementation
Course::Course(const std::string& code, int courseCredits, double grade)
    : courseCode(code), credits(courseCredits), numericGrade(grade) {}

// Private Helper Implementation
std::string Course::calculateLetterGrade() const {
    for (const auto& mapping : GRADE_TABLE) {
        if (numericGrade >= mapping.minScore) {
            return mapping.letter;
        }
    }
    return "F";
}

// Public Getters
std::string Course::getCourseCode() const { return courseCode; }
int Course::getCredits() const { return credits; }
double Course::getNumericGrade() const { return numericGrade; }
std::string Course::getLetterGrade() const { return calculateLetterGrade(); }

double Course::getGradePoints() const {
    for (const auto& mapping : GRADE_TABLE) {
        if (numericGrade >= mapping.minScore) {
            return mapping.points;
        }
    }
    return 0.0;
}

// Setter with validation entry point
void Course::setNumericGrade(double grade) {
    if (grade >= 0.0 && grade <= 100.0) {
        numericGrade = grade;
    }
}
