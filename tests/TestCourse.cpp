#include "Course.hpp"
#include <iostream>
#include <cassert>

void test_grade_mappings() {
    // Test Case 1: Perfect score should be an A
    Course c1("CS101", 3, 95.0);
    assert(c1.getLetterGrade() == "A");
    assert(c1.getGradePoints() == 4.0);

    // Test Case 2: Boundary check for B
    Course c2("MATH201", 4, 80.0);
    assert(c2.getLetterGrade() == "B");
    assert(c2.getGradePoints() == 3.0);

    // Test Case 3: Failing grade
    Course c3("PHYS101", 4, 45.0);
    assert(c3.getLetterGrade() == "F");
    assert(c3.getGradePoints() == 0.0);

    std::cout << "All Course unit tests passed successfully!\n";
}

int main() {
    test_grade_mappings();
    return 0;
}
