# الحد الأدنى من إصدار Qt المطلوب
QT_MIN_VERSION = 5.15.2

# إعدادات أساسية للمشروع
TARGET = wasslni
TEMPLATE = app
LANGUAGE = C++

# مكتبات Qt المطلوبة
QT += core gui widgets network

# إعدادات التهيئة
CONFIG += c++17 qt warn_on release
CONFIG += depend_includepath
CONFIG += c++11 utf8_source

QMAKE_CXXFLAGS += -MMD -MP
QMAKE_CXXFLAGS_WARN_ON += -Wall -Wextra -pedantic
QMAKE_CXXFLAGS_WARN_OFF += -Wno-unused-parameter

DEFINES += QT_DEPRECATED_WARNINGS

# إصدار Qt المطلوب
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += quick

# ملفات المصدر
SOURCES += \
    FileManager.cpp \
    Graph.cpp \
    GraphVisualizer.cpp \
    Login.cpp \
    Map.cpp \
    Options.cpp \
    PathManager.cpp \
    Register.cpp \
    User.cpp \
    UserManager.cpp \
    main.cpp

# ملفات الرؤوس
HEADERS += \
    FileManager.h \
    Graph.h \
    GraphVisualizer.h \
    Login.h \
    Map.h \
    Options.h \
    PathManager.h \
    Register.h \
    User.h \
    UserManager.h

# واجهات المستخدم
FORMS += \
    Login.ui

# ملفات الموارد
RESOURCES += \
    resources.qrc

# إعدادات خاصة بـ Windows
win32 {
    QMAKE_CXXFLAGS += -MP
    CONFIG += console
    DEFINES += _CRT_SECURE_NO_WARNINGS
}

# إعدادات خاصة بـ Linux/unix
unix {
    QMAKE_CXXFLAGS += -fPIC
}

# إعدادات التوزيع
target.path = $$[QT_INSTALL_BINS]
INSTALLS += target

# إعدادات لتصحيح الأخطاء في الوضع Debug
debug {
    CONFIG += console
    DEFINES += DEBUG_MODE
    QMAKE_CXXFLAGS += -g
}

# إعدادات للإصدار النهائي
release {
    DEFINES += QT_NO_DEBUG_OUTPUT
    QMAKE_CXXFLAGS += -O3
    unix:!macx {
        QMAKE_LFLAGS += -Wl,--gc-sections
    }
}
