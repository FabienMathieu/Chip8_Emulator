TEMPLATE = app

QT += qml quick

CONFIG += c++11


CONFIG(debug, debug|release) {
    win32 {
        OBJECTS_DIR = bin/Win32/obj/Debug/
        MOC_DIR = bin/Win32/moc/Debug/
        DESTDIR = bin/Win32/exe/Debug/
    }

    unix {
        OBJECTS_DIR = bin/unix/obj/Debug/
        MOC_DIR = bin/unix/moc/Debug/
        DESTDIR = bin/unix/exe/Debug/
    }
}

CONFIG(release, debug|release) {
    win32 {
        OBJECTS_DIR = bin/Win32/obj/Release/
        MOC_DIR = bin/Win32/moc/Release/
        DESTDIR = bin/Win32/exe/Release/
    }

    unix {
        OBJECTS_DIR = bin/unix/obj/Release/
        MOC_DIR = bin/unix/moc/Release/
        DESTDIR = bin/unix/exe/Release/
    }
}

INCLUDEPATH += src/

SOURCES += src/main.cpp \
    src/Chip8.cpp \
    src/Chip8Screen.cpp \
    src/Chip8ScreenProvider.cpp

RESOURCES += src/ui/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/Chip8.h \
    src/Chip8Screen.h \
    src/Chip8ScreenProvider.h
