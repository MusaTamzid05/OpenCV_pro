QT += core
QT -= gui

CONFIG += c++11

TARGET = ORB_Detector
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    orb_detector.cpp \
    helper.cpp

HEADERS += \
    orb_detector.h \
    helper.h

LIBS += `pkg-config --cflags --libs opencv`
