#BAR_Sox
#Un test de Sox pour le projet Boîte à rythmes.

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    BARSoxSound.cpp

LIBS += -LC:/Sox/sox-14.4.1rc3/src/.libs -llibsox
INCLUDEPATH += C:/Sox/sox-14.4.1rc3/src/

HEADERS += \
    BARSoxSound.h

