# 1. Create directories
New-Item -ItemType Directory -Path include, src, tests -Force

# 2. Create source files
New-Item -ItemType File -Path src/Main.cpp, src/Course.cpp, src/Semester.cpp, src/Student.cpp -Force

# 3. Create header files
New-Item -ItemType File -Path include/Course.hpp, include/Student.hpp, include/Semester.hpp -Force

# 4. Create root files
New-Item -ItemType File -Path README.md, .gitignore, LICENSE -Force