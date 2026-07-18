#include "Course.hpp"
#include "Semester.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

// Helper function to compare floating point numbers safely in C++
bool isClose(double a, double b, double epsilon = 0.001) {
    return std::abs(a - b) < epsilon;
}

void test_course_logic() {
    // Test Case 1: Standard A Grade
    Course c1("CS101", 3, 95.0);
    assert(c1.getLetterGrade() == "A");
    assert(c1.getGradePoints() == 4.0);

    // Test Case 2: Boundary check for B
    Course c2("MATH201", 4, 80.0);
    assert(c2.getLetterGrade() == "B");
    assert(c2.getGradePoints() == 3.0);

    std::cout << "  ==========  Individual Course unit tests passed!    ==========\n";
}

void test_semester_gpa_calculation() {
    // Set up a target semester
    Semester semester("Fall 2026");

    // Add courses with different credit weights and grades
    // CS101: 3 Credits, Grade: A (4.0 Points) -> Weight: 12.0
    // MATH201: 4 Credits, Grade: B (3.0 Points) -> Weight: 12.0
    // Total points = 24.0 | Total credits = 7
    // Expected GPA = 24.0 / 7 = 3.4285...
    
    semester.addCourse(Course("CS101", 3, 95.0));
    semester.addCourse(Course("MATH201", 4, 80.0));

    double expectedGpa = 24.0 / 7.0;
    double actualGpa = semester.calculateGPA();

    // Assert using our floating-point comparison helper
    assert(isClose(actualGpa, expectedGpa));

    std::cout << "  ========== Semester credit-weighted GPA calculation tests passed!  ==========\n";
}

void test_semester_edge_cases() {
    // Edge Case: Empty Semester should not crash (Division by Zero protection)
    Semester emptySemester("Spring 2026");
    assert(emptySemester.calculateGPA() == 0.0);

    std::cout << "  ========== Semester defensive edge-case tests passed!  ==========\n";
}

int main() {
    std::cout << "============= Starting Automated Test Suite ==========\n";
    
    test_course_logic();
    test_semester_gpa_calculation();
    // test_edge_cases();

    std::cout << "  ========== All system integration tests passed successfully.    ==========\n";
    return 0;
}
