# Enterprise CGPA Calculator
A production-grade, Obj-O C++ application designed to :
   - manage student academic profiles, 
   - calculate semester GPAs, and 
   - compute Cumulative Grade Point Averages (CGPA).

## Key Engineering Features
* **OO Architecture**: Clean separation of concerns (SoC)using isolated data layers (`Course`, `Semester`, `Student`).
* **RAII & Memory Safety**: Modern C++ standards utilizing smart pointers instead of risky raw memory pointers.
* **Data Persistence**: Robust file handling using `std::fstream` to save and reload student profiles smoothly.
* **Input Resilience**: Fail-safe input validation to prevent crashes from malformed user data.

## Tech Stack & Requirements
* **Language**: C++17 or higher
* **Compiler**: GCC / Clang / MSVC
* **Build System**: Terminal/CLI compilation (CMake integration planned)

## Directory Structure
* `include/` - Header files (`.hpp`) containing class blueprints.
* `src/` - Implementation files (`.cpp`) holding core business logic.
* `tests/` - Planned test suites for core arithmetic verification.

## Installation & Setup
1. Clone the repository:
   ```bash
   git clone https://github.com
   cd cgpa-calculator
   ```
2. Build the project (Instructions will be updated upon `Main.cpp` completion).
 