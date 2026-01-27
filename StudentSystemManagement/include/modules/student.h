#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    std::string id;
    std::string name;
    std::string email;
    std::string phone;
    std::string className;

public:
    Student();
    Student(
        const std::string& id,
        const std::string& name,
        const std::string& email,
        const std::string& phone,
        const std::string& className
    );

    // Getter
    std::string getId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getClassName() const;
};

#endif

