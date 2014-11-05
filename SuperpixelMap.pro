TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    slicsuperpixel.cpp

#OpenCV stuff
LIBS += `pkg-config opencv --libs`

#Enable Boost (if required)
LIBS += -L/usr/lib/ -lboost_filesystem -lboost_system -lboost_thread

#Enabling c++ '11 standard
QMAKE_CXXFLAGS += -std=c++11

#Enabling TBB
QMAKE_CXXFLAGS += -ltbb

HEADERS += \
    slicsuperpixel.h
