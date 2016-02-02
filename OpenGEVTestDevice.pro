#-------------------------------------------------
#
# Project created by QtCreator 2015-10-15T18:33:41
#
#-------------------------------------------------

QT       += core
QT       += network

QT += gui

TARGET = OpenGEVTestDevice
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    devicewrapper.cpp

HEADERS += \
    devicewrapper.h

QMAKE_CXXFLAGS+= -std=c++11

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/build-opengev-qt.3GCC-64bit-debug/release/ -lOpenGEV
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/build-opengev-qt.3GCC-64bit-debug/debug/ -lOpenGEV
else:unix {
    CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/build-opengev-qt4.8GCC-64bit-debug -lOpenGEV
    CONFIG(release, release|debug): LIBS += -L$$PWD/../build/build-opengev-qt4.8GCC-64bit-release -lOpenGEV
}

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

    INCLUDEPATH += /usr/include/boost \
                   /usr/include/openni2 \
                   /usr/local/include/log4cpp \
                   /usr/local/include/libfreenect2

    LIBS += "-L/usr/lib" \
             -lboost_system

    LIBS += -L/usr/local/lib

    LIBS += -llog4cpp

    LIBS += -lOpenNI2

    LIBS += -lfreenect2
