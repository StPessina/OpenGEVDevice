#-------------------------------------------------
#
# Project created by QtCreator 2015-10-15T18:33:41
#
#-------------------------------------------------

QT       += core
QT       += network

QT += gui

TARGET = OpenGVTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    devicewrapper.cpp

HEADERS += \
    devicewrapper.h

QMAKE_CXXFLAGS+= -std=c++11

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/build-desktop-qt.3GCC-64bit-debug/release/ -lOpenGV
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/build-desktop-qt.3GCC-64bit-debug/debug/ -lOpenGV
else:unix {
    CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/build-desktop-qt4.8GCC-64bit-debug -lOpenGV
    CONFIG(release, release|debug): LIBS += -L$$PWD/../build/build-desktop-qt4.8GCC-64bit-release -lOpenGV
}

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

    INCLUDEPATH += /usr/local/include/log4cpp \
                   /usr/include/boost \
                   /usr/include/openni2

    LIBS += "-L/usr/lib" \
             -lboost_system

    LIBS += -L/usr/local/lib

    LIBS += -llog4cpp

    LIBS += -lOpenNI2
