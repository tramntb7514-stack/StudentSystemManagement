#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include <vector>
#include <iostream>
#include "../modules/student.h"

class StudentManager {
private:
    std::vector<Student> students;

public:
    // CRUD
    void addStudent(const Student& student);
    bool removeStudentById(const std::string& id);
    Student* findStudentById(const std::string& id);

    void showAllStudents() const;
};

#endif

