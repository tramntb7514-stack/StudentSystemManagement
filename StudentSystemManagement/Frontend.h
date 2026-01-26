#ifndef FRONTEND_H
#define FRONTEND_H
#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <vector>
#include "auth.h"

using namespace Gdiplus;

// Hàm vẽ hình chữ nhật bo góc cho giao diện hiện đại
inline void FillRoundRect(Graphics& g, Brush* b, int x, int y, int w, int h, int r) {
    GraphicsPath path;
    path.AddArc(x, y, r, r, 180, 90);
    path.AddArc(x + w - r, y, r, r, 270, 90);
    path.AddArc(x + w - r, y + h - r, r, r, 0, 90);
    path.AddArc(x, y + h - r, r, r, 90, 90);
    g.FillPath(b, &path);
}

// Giao diện chính sau khi đăng nhập
inline void DrawDashboard(Graphics& g, RECT r, Session session, const std::vector<UserData>& users) {
    g.SetSmoothingMode(SmoothingModeAntiAlias);
    g.Clear(Color(255, 240, 242, 245)); // Màu nền xám nhạt

    // Vẽ Sidebar xanh bên trái
    SolidBrush sideBr(Color(255, 0, 80, 82));
    g.FillRectangle(&sideBr, 0, 0, 250, r.bottom);

    FontFamily ff(L"Segoe UI");
    Font fT(&ff, 13, FontStyleBold, UnitPoint);
    Font fWelcome(&ff, 18, FontStyleBold, UnitPoint);
    Font fM(&ff, 10, FontStyleRegular, UnitPoint);
    
    SolidBrush w(Color(255, 255, 255)), b(Color(255, 33, 37, 41));
    SolidBrush red(Color(255, 220, 53, 69)), green(Color(255, 40, 167, 69));

    // Hiển thị Vai trò trên Sidebar
    std::wstring rSide = (session.role == ADMIN) ? L"QUẢN TRỊ VIÊN" : 
                         (session.role == LECTURER ? L"GIẢNG VIÊN" : L"SINH VIÊN");
    g.DrawString(rSide.c_str(), -1, &fT, PointF(30, 80), &w);

    // --- HIỂN THỊ LỜI CHÀO MỪNG CÁ NHÂN HÓA ---
    std::wstring welcomeMsg;
    if (session.role == ADMIN) welcomeMsg = L"Chào mừng Quản trị viên: " + session.username;
    else if (session.role == LECTURER) welcomeMsg = L"Chào mừng Giảng viên: " + session.username;
    else welcomeMsg = L"Chào mừng Sinh viên: " + session.username;

    g.DrawString(welcomeMsg.c_str(), -1, &fWelcome, PointF(280, 40), &b);
    
    // Vẽ đường kẻ ngăn cách (Đã sửa lỗi Pen)
    Pen linePen(Color(255, 200, 200, 200), 1);
    g.DrawLine(&linePen, 280, 85, 1100, 85);

    // Nội dung chính cho Admin
    if (session.role == ADMIN) {
        g.DrawString(L"DANH SÁCH TÀI KHOẢN HỆ THỐNG", -1, &fT, PointF(280, 110), &b);
        int y = 160;
        for (const auto& u : users) {
            if (u.username == L"admin") continue;
            std::wstring info = u.username + (u.role == ADMIN ? L" (Admin)" : (u.role == LECTURER ? L" (GV)" : L" (SV)"));
            if (!u.isApproved) info += L" - [Chờ duyệt]";
            
            g.DrawString(info.c_str(), -1, &fM, PointF(300, y), &b);
            
            if (!u.isApproved) {
                g.FillRectangle(&green, 750, y - 5, 70, 25);
                g.DrawString(L"Duyệt", -1, &fM, PointF(765, y - 2), &w);
            }
            g.FillRectangle(&red, 830, y - 5, 70, 25);
            g.DrawString(L"Xóa", -1, &fM, PointF(850, y - 2), &w);
            y += 40;
        }
    } else {
        g.DrawString(L"Bạn đã đăng nhập thành công vào hệ thống quản lý.", -1, &fM, PointF(280, 110), &b);
    }

    // Nút Đăng xuất
    FillRoundRect(g, &red, 30, r.bottom - 80, 190, 45, 10);
    g.DrawString(L"↪ ĐĂNG XUẤT", -1, &fM, PointF(65, r.bottom - 68), &w);
}

// Vẽ màn hình Đăng nhập/Đăng ký
inline void DrawModernPortal(Graphics& g, RECT r, bool isRegister) {
    g.SetSmoothingMode(SmoothingModeAntiAlias);
    LinearGradientBrush bg(Rect(0, 0, r.right, r.bottom), Color(255, 0, 121, 124), Color(255, 0, 70, 72), LinearGradientModeVertical);
    g.FillRectangle(&bg, 0, 0, r.right, r.bottom);

    SolidBrush card(Color(255, 255, 255));
    FillRoundRect(g, &card, 730, 100, 360, 580, 25);

    FontFamily ff(L"Segoe UI");
    Font fT(&ff, 20, FontStyleBold, UnitPoint);
    Font fS(&ff, 9, FontStyleRegular, UnitPoint);
    SolidBrush mBr(Color(255, 0, 80, 82));
    SolidBrush gBr(Color(255, 120, 120, 120));

    g.DrawString(isRegister ? L"ĐĂNG KÝ" : L"ĐĂNG NHẬP", -1, &fT, PointF(765, 150), &mBr);
    g.DrawString(L"Tên đăng nhập:", -1, &fS, PointF(770, 210), &gBr);
    g.DrawString(L"Mật khẩu:", -1, &fS, PointF(770, 280), &gBr);
    g.DrawString(L"Vai trò (0:Admin, 1:GV, 2:SV):", -1, &fS, PointF(770, 365), &mBr);
}
#endif