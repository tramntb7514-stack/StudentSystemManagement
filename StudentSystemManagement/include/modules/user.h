#ifndef USER_H
#define USER_H
#include <string>

struct User {
    std::wstring username;
    std::wstring password;
    int role;
    std::wstring status;
};
#endif