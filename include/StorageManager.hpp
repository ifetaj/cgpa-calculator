#ifndef STORAGE_MANAGER_HPP
#define STORAGE_MANAGER_HPP

#include <string>
#include "Student.hpp"

class StorageManager {
public:
    // Saves a student's full transcript data to a flat text file
    static bool saveProfile(const std::string& filename, const Student& student);

    // Loads a student's data and returns a Student object
    static bool loadProfile(const std::string& filename, Student& outStudent);
};

#endif // STORAGE_MANAGER_HPP
