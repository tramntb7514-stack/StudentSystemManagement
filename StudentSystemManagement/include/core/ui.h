#ifndef UI_H
#define UI_H

#include <iostream>
using namespace std;

inline void showMainMenu() {
    cout << "=============================\n";
    cout << "  STUDENT MANAGEMENT SYSTEM\n";
    cout << "=============================\n";
    cout << "1. Student\n";
    cout << "2. Lecturer\n";
    cout << "3. Admin\n";
    cout << "0. Exit\n";
    cout << "-----------------------------\n";
    cout << "Choose: ";
}

#endif

