#include <iostream>
#include <string>
#include <limits>
#include "Student.hpp"
#include "Semester.hpp"
#include "Course.hpp"

// Utility helper to safely clear input stream errors (Enterprise Input Resilience)
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Visual interface component: Display Menu Options
void displayMenu() {
    std::cout << "\n====================================\n";
    std::cout << "              CGPA CALCULATOR        \n";
    std::cout << "====================================\n";
    std::cout << "1. Add a Semester\n";
    std::cout << "2. Add a Course to a Semester\n";
    std::cout << "3. View Academic Report & GPA/CGPA\n";
    std::cout << "4. Exit Application\n";
    std::cout << "Select an option (1-4): ";
}

int main() {
    std::cout << "Welcome to the Academic Management Console.\n";
    std::string firstName, lastName;
    
    std::cout << "Enter student first name: ";
    std::cin >> firstName;
    std::cout << "Enter student last name: ";
    std::cin >> lastName;
    clearInputBuffer();

    // Initialize core tracking object
    Student student(firstName, lastName);
    
    bool running = true;
    while (running) {
        displayMenu();
        int choice;
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 4) {
            std::cout << "Invalid choice! Please enter a number between 1 and 4.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                std::string semCode;
                std::cout << "Enter Semester Code (e.g., Fall2026, Spring2027): ";
                std::cin >> semCode;
                student.addSemester(Semester(semCode));
                std::cout << "Semester '" << semCode << "' successfully added.\n";
                break;
            }
            case 2: {
                auto& semesters = const_cast<std::vector<Semester>&>(student.getSemesters());
                if (semesters.empty()) {
                    std::cout << "Error: Create a semester first before adding courses.\n";
                    break;
                }

                std::cout << "Select semester to add course to:\n";
                for (size_t i = 0; i < semesters.size(); ++i) {
                    std::cout << i + 1 << ". " << semesters[i].getSemesterCode() << "\n";
                }
                std::cout << "Choice: ";
                size_t semChoice;
                std::cin >> semChoice;

                if (std::cin.fail() || semChoice < 1 || semChoice > semesters.size()) {
                    std::cout << "Invalid selection.\n";
                    clearInputBuffer();
                    break;
                }

                std::string code;
                int credits;
                double grade;

                std::cout << "Enter Course Code (e.g., CS101): ";
                std::cin >> code;
                std::cout << "Enter Credits (1-5): ";
                std::cin >> credits;
                std::cout << "Enter Numeric Grade (0-100): ";
                std::cin >> grade;

                if (std::cin.fail() || grade < 0 || grade > 100 || credits < 1) {
                    std::cout << "Invalid course inputs. Data discarded.\n";
                    clearInputBuffer();
                    break;
                }

                semesters[semChoice - 1].addCourse(Course(code, credits, grade));
                std::cout << "Course added successfully!\n";
                break;
            }
            case 3: {
                std::cout << "\n====================================\n";
                std::cout << "🎓 ACADEMIC TRANSCRIPT: " << student.getFirstName() << " " << student.getLastName() << "\n";
                std::cout << "====================================\n";

                if (student.getSemesters().empty()) {
                    std::cout << "No academic history available.\n";
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
            case 4:
                std::cout << "Thank you for using Enterprise Academic Systems. Exiting...\n";
                running = false;
                break;
        }
    }
    return 0;
}
