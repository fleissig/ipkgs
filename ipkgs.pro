TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    functions.cpp

HEADERS += \
    functions.h

QMAKE_CXXFLAGS += -std=c++11
