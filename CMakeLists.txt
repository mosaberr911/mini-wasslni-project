cmake_minimum_required(VERSION 3.30)
project(mini_wasslni_project)

set(CMAKE_CXX_STANDARD 20)

# تحديد مسار Qt6Config.cmake
#set(Qt6_DIR "C:/Qt/6.9.0/mingw_64/lib/cmake/Qt6")
set(Qt6_DIR "/Users/mohamed/Qt/6.9.0/macos/lib/cmake/Qt6")

# البحث عن Qt والمكتبات المطلوبة
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# إضافة الملفات المصدرية
add_executable(mini_wasslni_project main.cpp Graph.cpp Graph.h
        User.cpp
        User.h
        ConsoleApp.cpp
        ConsoleApp.h)

# ربط Qt مع المشروع
target_link_libraries(mini_wasslni_project Qt6::Widgets)
