TEMPLATE = app

QT += qml quick

CONFIG += c++11


CONFIG(debug, debug|release) {
    win32 {
        OBJECTS_DIR = ../bin/Win32/obj/Debug/
        MOC_DIR = ../bin/Win32/moc/Debug/
        DESTDIR = ../bin/Win32/exe/Debug/
    }

    unix {
        OBJECTS_DIR = ../bin/unix/obj/Debug/
        MOC_DIR = ../bin/unix/moc/Debug/
        DESTDIR = ../bin/unix/exe/Debug/
    }
}

CONFIG(release, debug|release) {
    win32 {
        OBJECTS_DIR = ../bin/Win32/obj/Release/
        MOC_DIR = ../bin/Win32/moc/Release/
        DESTDIR = ../bin/Win32/exe/Release/
    }

    unix {
        OBJECTS_DIR = ../bin/unix/obj/Release/
        MOC_DIR = ../bin/unix/moc/Release/
        DESTDIR = ../bin/unix/exe/Release/
    }
}

SOURCES += main.cpp \
    Chip8.cpp \
    Chip8Screen.cpp \
    Chip8ScreenProvider.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Chip8.h \
    Chip8Screen.h \
    Chip8ScreenProvider.h
