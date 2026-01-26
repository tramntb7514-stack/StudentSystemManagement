#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include "auth.h"
#include "database.h" // Đảm bảo bạn có file database.h để xử lý file users_data.txt
#include "Frontend.h"

#define ID_BTN_ACTION 101
#define ID_BTN_SWITCH 102

Session currentSession = { L"", NONE, false };
bool isRegisterMode = false;
HWND hU, hP, hR, hB, hS;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE: {
            HFONT hF = CreateFontW(18, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 3, 0, L"Segoe UI");
            hU = CreateWindowExW(0, L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 770, 230, 280, 35, hwnd, NULL, NULL, NULL);
            hP = CreateWindowExW(0, L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 770, 300, 280, 35, hwnd, NULL, NULL, NULL);
            hR = CreateWindowExW(0, L"Edit", L"2", WS_VISIBLE | WS_CHILD | WS_BORDER, 770, 390, 280, 35, hwnd, NULL, NULL, NULL);
            hB = CreateWindowW(L"Button", L"XÁC NHẬN", WS_VISIBLE | WS_CHILD, 770, 460, 280, 50, hwnd, (HMENU)ID_BTN_ACTION, NULL, NULL);
            hS = CreateWindowW(L"Button", L"Chưa có tài khoản? Đăng ký", WS_VISIBLE | WS_CHILD | BS_FLAT, 770, 530, 280, 30, hwnd, (HMENU)ID_BTN_SWITCH, NULL, NULL);
            SendMessage(hU, WM_SETFONT, (WPARAM)hF, TRUE); SendMessage(hP, WM_SETFONT, (WPARAM)hF, TRUE); SendMessage(hR, WM_SETFONT, (WPARAM)hF, TRUE);
            break;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps; HDC hdc = BeginPaint(hwnd, &ps);
            Graphics g(hdc); RECT r; GetClientRect(hwnd, &r);
            if (!currentSession.isLoggedIn) DrawModernPortal(g, r, isRegisterMode);
            else DrawDashboard(g, r, currentSession, g_users);
            EndPaint(hwnd, &ps); break;
        }
        case WM_LBUTTONDOWN: {
            int x = LOWORD(lp), y = HIWORD(lp); RECT r; GetClientRect(hwnd, &r);
            // Click nút Đăng xuất
            if (currentSession.isLoggedIn && x >= 30 && x <= 220 && y >= r.bottom - 80 && y <= r.bottom - 35) {
                currentSession.isLoggedIn = false;
                ShowWindow(hU, SW_SHOW); ShowWindow(hP, SW_SHOW); ShowWindow(hR, SW_SHOW); ShowWindow(hB, SW_SHOW); ShowWindow(hS, SW_SHOW);
                InvalidateRect(hwnd, NULL, TRUE);
            }
            // Xử lý nút Duyệt/Xóa cho Admin
            if (currentSession.isLoggedIn && currentSession.role == ADMIN) {
                int itemY = 160;
                for (int i = 0; i < g_users.size(); i++) {
                    if (g_users[i].username == L"admin") continue;
                    if (x >= 750 && x <= 820 && y >= itemY - 5 && y <= itemY + 20 && !g_users[i].isApproved) {
                        ApproveUser(g_users[i].username); InvalidateRect(hwnd, NULL, TRUE); break;
                    }
                    if (x >= 830 && x <= 900 && y >= itemY - 5 && y <= itemY + 20) {
                        DeleteUser(g_users[i].username); InvalidateRect(hwnd, NULL, TRUE); break;
                    }
                    itemY += 40;
                }
            }
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wp) == ID_BTN_SWITCH) {
                isRegisterMode = !isRegisterMode;
                SetWindowTextW(hS, isRegisterMode ? L"Quay lại Đăng nhập" : L"Chưa có tài khoản? Đăng ký");
                InvalidateRect(hwnd, NULL, TRUE);
            }
            if (LOWORD(wp) == ID_BTN_ACTION) {
                wchar_t u[50], p[50], rStr[10];
                GetWindowTextW(hU, u, 50); GetWindowTextW(hP, p, 50); GetWindowTextW(hR, rStr, 10);
                int roleInt = _wtoi(rStr);
                if (isRegisterMode) {
                    RegisterAccount(u, p, roleInt);
                    MessageBoxW(hwnd, L"Đăng ký xong! Chờ Admin duyệt.", L"Thông báo", MB_OK);
                    SendMessage(hwnd, WM_COMMAND, ID_BTN_SWITCH, 0);
                } else {
                    Role role = AuthenticateUser(u, p, (Role)roleInt);
                    if (role != NONE) {
                        currentSession = { u, role, true };
                        ShowWindow(hU, SW_HIDE); ShowWindow(hP, SW_HIDE); ShowWindow(hR, SW_HIDE); ShowWindow(hB, SW_HIDE); ShowWindow(hS, SW_HIDE);
                        InvalidateRect(hwnd, NULL, TRUE);
                    } else MessageBoxW(hwnd, L"Lỗi đăng nhập hoặc tài khoản chưa duyệt!", L"Lỗi", MB_ICONERROR);
                }
            }
            break;
        }
        case WM_DESTROY: PostQuitMessage(0); break;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE h, HINSTANCE, LPSTR, int n) {
    LoadDatabase();
    ULONG_PTR t; GdiplusStartupInput si; GdiplusStartup(&t, &si, NULL);
    WNDCLASSW wc = {0}; wc.lpfnWndProc = WndProc; wc.hInstance = h; wc.hCursor = LoadCursor(NULL, IDC_ARROW); wc.lpszClassName = L"STUDENT_SYS";
    RegisterClassW(&wc);
    HWND hwnd = CreateWindowExW(0, L"STUDENT_SYS", L"Hệ thống Quản lý Sinh viên", WS_OVERLAPPEDWINDOW, 100, 50, 1200, 750, 0, 0, h, 0);
    ShowWindow(hwnd, n);
    MSG m; while (GetMessage(&m, 0, 0, 0)) { TranslateMessage(&m); DispatchMessage(&m); }
    GdiplusShutdown(t); return 0;
}