#ifndef BACKEND_H
#define BACKEND_H
#include <string>

// Địa chỉ IP của Server hệ thống
const std::wstring SERVER_IP = L"192.168.1.105";

inline bool Authenticate(std::wstring user, std::wstring pass) {
    if (user == L"admin" && pass == L"123") return true;
    return false;
}
#endif