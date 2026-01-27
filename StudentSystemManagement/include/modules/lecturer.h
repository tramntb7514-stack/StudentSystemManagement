#ifndef LECTURER_H
#define LECTURER_H

#include <string>

class Lecturer {
private:
    std::string id;
    std::string name;
    std::string email;
    std::string phone;
    std::string department;

public:
    Lecturer();
    Lecturer(
        const std::string& id,
        const std::string& name,
        const std::string& email,
        const std::string& phone,
        const std::string& department
    );

    // Getter
    std::string getId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getDepartment() const;
};

#endif

