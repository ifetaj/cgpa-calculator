#include <iostream>
#include <string>
#include <limits>
#include "Student.hpp"
#include "Semester.hpp"
#include "Course.hpp"
#include "StorageManager.hpp"

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayMenu() {
    std::cout << "\n========================================================\n";
    std::cout << "==   ##########      CGPA CALCULATOR     ###########  ==\n";
    std::cout << "========================================================\n";
    std::cout << "1. Add a Semester\n";
    std::cout << "2. Add a Course to a Semester\n";
    std::cout << "3. View Academic Report & GPA/CGPA\n";
    std::cout << "4. Save Academic Profile to File\n";
    std::cout << "5. Load Academic Profile from File\n";
    std::cout << "6. Exit Application\n";
    std::cout << "Select an option (1-6): ";
}

int main() {
    std::cout << "##### Welcome to the Academic Management Console. #####\n";
    Student student("Default", "Student");
    
    std::cout << "-----Initialize a new profile or load an existing one?\n";
    std::cout << "-----1. Create New Profile\n-----2. Load from File\n-----3. Exit\nChoice: ";
    int initChoice;
    std::cin >> initChoice;
    clearInputBuffer();

    if (initChoice == 2) {
        std::string filename;
        std::cout << "Enter filename to load (e.g., transcript.txt): ";
        std::cin >> filename;
        if (StorageManager::loadProfile(filename, student)) {
            std::cout << " Profile successfully loaded for " << student.getFirstName() << " " << student.getLastName() << "\n";
        } else {
            std::cout << " Failed to load file. Initializing blank profile instead.\n";
        }
    } else {
        std::string firstName, lastName;
        std::cout << "Enter student first name: ";
        std::cin >> firstName;
        std::cout << "Enter student last name: ";
        std::cin >> lastName;
        student.setFirstName(firstName);
        student.setLastName(lastName);
        clearInputBuffer();
    }
    
    bool running = true;
    while (running) {
        displayMenu();
        int choice;
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 6) {
            std::cout << " Invalid choice! Please enter a number between 1 and 6.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                std::string semCode;
                std::cout << "Enter Semester Code (e.g., Fall2026): ";
                std::cin >> semCode;
                student.addSemester(Semester(semCode));
                std::cout << " Semester '" << semCode << "' added.\n";
                break;
            }
            case 2: {
                // Workaround to bypass const vector access safely inside Main interface context
                auto& semesters = const_cast<std::vector<Semester>&>(student.getSemesters());
                if (semesters.empty()) {
                    std::cout << " Error: Create a semester first.\n";
                    break;
                }

                std::cout << "Select semester:\n";
                for (size_t i = 0; i < semesters.size(); ++i) {
                    std::cout << i + 1 << ". " << semesters[i].getSemesterCode() << "\n";
                }
                size_t semChoice;
                std::cin >> semChoice;

                if (std::cin.fail() || semChoice < 1 || semChoice > semesters.size()) {
                    std::cout << " Invalid selection.\n";
                    clearInputBuffer();
                    break;
                }

                std::string code;
                int credits;
                double grade;

                std::cout << "Enter Course Code: ";
                std::cin >> code;
                std::cout << "Enter Credits (1-5): ";
                std::cin >> credits;
                std::cout << "Enter Numeric Grade (0-100): ";
                std::cin >> grade;

                if (std::cin.fail() || grade < 0 || grade > 100 || credits < 1) {
                    std::cout << " Invalid course inputs. Data discarded.\n";
                    clearInputBuffer();
                    break;
                }

                semesters[semChoice - 1].addCourse(Course(code, credits, grade));
                std::cout << " Course added successfully!\n";
                break;
            }
            case 3: {
                std::cout << "\n====================================\n";
                std::cout << " ACADEMIC TRANSCRIPT: " << student.getFirstName() << " " << student.getLastName() << "\n";
                std::cout << "====================================\n";

                if (student.getSemesters().empty()) {
                    std::cout << "No academic history found.\n";
                    break;
                }

                for (const auto& semester : student.getSemesters()) {
                    std::cout << "\n Semester: " << semester.getSemesterCode() << "\n";
                    std::cout << "------------------------------------\n";
                    for (const auto& course : semester.getCourses()) {
                        std::cout << "  - " << course.getCourseCode() 
                                  << " | Credits: " << course.getCredits()
                                  << " | Grade: " << course.getNumericGrade()
                                  << " (" << course.getLetterGrade() << ")\n";
                    }
                    std::cout << "   Semester GPA: " << semester.calculateGPA() << "\n";
                }
                std::cout << "------------------------------------\n";
                std::cout << " Cumulative CGPA: " << student.calculateCGPA() << "\n";
                break;
            }
            case 4: {
                std::string filename;
                std::cout << "Enter filename to save data (e.g., transcript.txt): ";
                std::cin >> filename;
                if (StorageManager::saveProfile(filename, student)) {
                    std::cout << " Profile successfully saved to " << filename << "\n";
                } else {
                    std::cout << " Error writing to file.\n";
                }
                break;
            }
            case 5: {
                std::string filename;
                std::cout << "Enter filename to load: ";
                std::cin >> filename;
                // Create a temporary blank student to fill up cleanly
                Student tempStudent("Temp", "User");
                if (StorageManager::loadProfile(filename, tempStudent)) {
                    student = tempStudent; // Safe assignment override
                    std::cout << " Profile loaded successfully from " << filename << "\n";
                } else {
                    std::cout << " Failed to open file.\n";
                }
                break;
            }
            case 6:
                std::cout << "Exiting application. Goodbye.\n";
                running = false;
                break;
        }
    }
    return 0;
}
