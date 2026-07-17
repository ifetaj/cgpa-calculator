#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>

class Course {
private:
    std::string courseCode;
    int credits;
    double numericGrade; // Scale out of 100 or 4.0

    // Private helper function to determine letter grade from numeric grade
    std::string calculateLetterGrade() const;

public:
    // Constructor
    Course(const std::string& code, int courseCredits, double grade);

    // Getters
    std::string getCourseCode() const;
    int getCredits() const;
    double getNumericGrade() const;
    std::string getLetterGrade() const;
    double getGradePoints() const; // e.g., converts 'A' to 4.0, 'B' to 3.0

    // Setters
    void setNumericGrade(double grade);
};

#endif // COURSE_HPP
