TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += main.cpp \
    celllist.cpp \
    vec3.cpp \
    filemanager.cpp \
    twopointcorrelationfunction.cpp \
    cpelapsedtimer.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    celllist.h \
    vec3.h \
    filemanager.h \
    twopointcorrelationfunction.h \
    cpelapsedtimer.h

