#include "Student.hpp"
#include <string>
#include <vector>

// Constructor
Student::Student(const std::string& fName, const std::string& lName) 
    : firstName(fName), lastName(lName) {}

// Getters
std::string Student::getFirstName() const { 
    return firstName; 
}

std::string Student::getLastName() const { 
    return lastName; 
}

const std::vector<Semester>& Student::getSemesters() const { 
    return semesters;
}

// Setters
void Student::setFirstName(const std::string& fName) { 
    firstName = fName; 
}

void Student::setLastName(const std::string& lName) { 
    lastName = lName; 
}

// Logic Methods: Add an entire semester block to the student profile
void Student::addSemester(const Semester& semester) {
    semesters.push_back(semester);
}

// Logic Methods: Calculate Global Cumulative GPA (CGPA)
double Student::calculateCGPA() const {
    if (semesters.empty()) {
        return 0.0;
    }

    double totalWeightedGpa = 0.0;
    int totalSemesterCredits = 0;

    // Loop through each semester to calculate a cumulative weighted average
    for (const auto& semester : semesters) {
        int semesterCredits = 0;
        
        // Calculate the total credits within this specific semester
        for (const auto& course : semester.getCourses()) {
            semesterCredits += course.getCredits();
        }

        // Add this semester's contributions to the global calculation
        totalWeightedGpa += (semester.calculateGPA() * semesterCredits);
        totalSemesterCredits += semesterCredits;
    }

    // Defensive check to avoid division by zero
    if (totalSemesterCredits == 0) {
        return 0.0;
    }

    return totalWeightedGpa / totalSemesterCredits;
}
