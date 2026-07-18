#include "StorageManager.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

bool StorageManager::saveProfile(const std::string& filename, const Student& student) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        return false;
    }

    // 1. Write Student Info
    outFile << "STU:" << student.getFirstName() << "," << student.getLastName() << "\n";

    // 2. Iterate through Semesters
    for (const auto& semester : student.getSemesters()) {
        outFile << "SEM:" << semester.getSemesterCode() << "\n";

        // 3. Iterate through Courses inside that semester
        for (const auto& course : semester.getCourses()) {
            outFile << "CRS:" << course.getCourseCode() << "," 
                    << course.getCredits() << "," 
                    << course.getNumericGrade() << "\n";
        }
    }

    outFile.close();
    return true;
}

bool StorageManager::loadProfile(const std::string& filename, Student& outStudent) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return false;
    }

    std::string line;
    Semester* currentSemester = nullptr;
    std::vector<Semester> tempSemesters;

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        std::string tag = line.substr(0, 4);
        std::string data = line.substr(4);
        std::stringstream ss(data);

        if (tag == "STU:") {
            std::string fName, lName;
            std::getline(ss, fName, ',');
            std::getline(ss, lName);
            outStudent.setFirstName(fName);
            outStudent.setLastName(lName);
        } 
        else if (tag == "SEM:") {
            std::string semCode;
            std::getline(ss, semCode);
            tempSemesters.push_back(Semester(semCode));
            currentSemester = &tempSemesters.back();
        } 
        else if (tag == "CRS:") {
            if (currentSemester == nullptr) continue; // Malformed file protection
            
            std::string code, creditsStr, gradeStr;
            std::getline(ss, code, ',');
            std::getline(ss, creditsStr, ',');
            std::getline(ss, gradeStr);

            int credits = std::stoi(creditsStr);
            double grade = std::stod(gradeStr);
            
            currentSemester->addCourse(Course(code, credits, grade));
        }
    }

    inFile.close();

    // Reconstruct student profile with populated semesters
    for (const auto& sem : tempSemesters) {
        outStudent.addSemester(sem);
    }

    return true;
}
