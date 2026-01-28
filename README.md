# Student System Management

## Mô tả dự án

Hệ thống quản lý sinh viên sử dụng C++.

## Cấu trúc thư mục

```
StudentSystemManagement/
├── Backend.h
├── Frontend.h
├── main.cpp
├── main.h              Chương trình chính
├── README.md           Tài liệu description
├── users_data.txt
├── data/
│   └── file.txt
├── docs/
│   └── name.docs
└── include/
    ├── core/
    │   ├── auth.h
    │   ├── database.h
    │   ├── system.h
    │   └── ui.h            Giao diện console, menu
    ├── managers/
    │   ├── class_manager.h
    │   ├── course_manager.h
    │   ├── grade_manager.h
    │   ├── lecturer_manager.h
    │   ├── report_manager.h
    │   ├── schedule_manager.h
    │   └── student_manager.h
    ├── modules/
    │   ├── assignment.h
    │   ├── class_section.h
    │   ├── course.h
    │   ├── grade.h
    │   ├── lecturer.h
    │   ├── schedule.h
    │   ├── student.h
    │   └── user.h
    └── utils/
        ├── config.h
        ├── constants.h
        ├── file_io.h
        ├── helpers.h
        └── validation.h
```