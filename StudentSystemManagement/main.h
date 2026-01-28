#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include "core/ui.h"

using namespace std;

/* ===== GIẢ DATABASE (THAY database.h) ===== */
vector<User> g_users = {
    {"admin", "admin", ADMIN, true}
};

/* ===== GIỮ NGUYÊN NGHIỆP VỤ ===== */
void LoadDatabase() {
    // giả lập load
}

void RegisterAccount(string u, string p, int role) {
    g_users.push_back({u, p, (Role)role, false});
}

Role AuthenticateUser(string u, string p, Role role) {
    for (auto& user : g_users) {
        if (user.username == u &&
            user.password == p &&
            user.role == role &&
            user.isApproved)
            return user.role;
    }
    return NONE;
}

void ApproveUser(const string& name) {
    for (auto& u : g_users)
        if (u.username == name)
            u.isApproved = true;
}

void DeleteUser(const string& name) {
    for (auto it = g_users.begin(); it != g_users.end(); ++it) {
        if (it->username == name) {
            g_users.erase(it);
            return;
        }
    }
}

/* ===== MAIN (THAY WinMain) ===== */
int main() {
    LoadDatabase();

    Session currentSession = {"", NONE, false};
    bool isRegisterMode = false;

    while (true) {
        if (!currentSession.isLoggedIn) {
            DrawModernPortal(isRegisterMode);

            string u, p;
            int role;

            cout << "Username: "; cin >> u;
            cout << "Password: "; cin >> p;
            cout << "Role (1-STUDENT,2-LECTURER,3-ADMIN): ";
            cin >> role;

            if (isRegisterMode) {
                RegisterAccount(u, p, role);
                cout << "Dang ky thanh cong! Cho admin duyet.\n";
                isRegisterMode = false;
            } else {
                Role r = AuthenticateUser(u, p, (Role)role);
                if (r != NONE) {
                    currentSession = {u, r, true};
                } else {
                    cout << "Dang nhap that bai hoac chua duyet!\n";
                }
            }

            cout << "\n0. Thoat | 1. Chuyen Dang nhap/Dang ky: ";
            int c; cin >> c;
            if (c == 0) break;
            if (c == 1) isRegisterMode = !isRegisterMode;
        }
        else {
            DrawDashboard(currentSession, g_users);

            if (currentSession.role == ADMIN) {
                cout << "\nNhap ten user can duyet (hoac 0 bo qua): ";
                string name; cin >> name;
                if (name != "0") ApproveUser(name);

                cout << "Nhap ten user can xoa (hoac 0 bo qua): ";
                cin >> name;
                if (name != "0") DeleteUser(name);
            }

            int c;
            cout << "Chon: "; cin >> c;
            if (c == 1) {
                currentSession = {"", NONE, false};
            }
        }
    }

    return 0;
}

#endif
