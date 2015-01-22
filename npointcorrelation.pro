TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS += -xCORE-AVX-I -O3 -ipo -falign-functions=16 -vec-report2
QMAKE_CFLAGS += -xCORE-AVX-I -O3 -ipo -falign-functions=16 -vec-report2
QMAKE_LFLAGS += -vec-report2

SOURCES += main.cpp \
    celllist.cpp \
    vec3.cpp \
    filemanager.cpp \
    twopointcorrelationfunction.cpp \
    cpelapsedtimer.cpp \
    random.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    celllist.h \
    vec3.h \
    filemanager.h \
    twopointcorrelationfunction.h \
    cpelapsedtimer.h \
    random.h

