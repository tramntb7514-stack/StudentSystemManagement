#ifndef LECTURER_MANAGER_H
#define LECTURER_MANAGER_H

#include <vector>
#include <iostream>
#include "../modules/lecturer.h"

class LecturerManager {
private:
    std::vector<Lecturer> lecturers;

public:
    // CRUD
    void addLecturer(const Lecturer& lecturer);
    bool removeLecturerById(const std::string& id);
    Lecturer* findLecturerById(const std::string& id);

    void showAllLecturers() const;
};

#endif

