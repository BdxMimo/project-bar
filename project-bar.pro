#-------------------------------------------------
#
# Project created by QtCreator 2013-02-07T08:48:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project-bar
TEMPLATE = app



SOURCES += src/main.cpp\
    src/barwindow.cpp \
    ui/barsoundbar.cpp \
    ui/bartabpattern.cpp \
    ui/bargauge.cpp \
    ui/bartabsong.cpp \
    ui/barpatternbar.cpp



HEADERS  += src/barwindow.h \
    ui/barsoundbar.h \
    ui/bartabpattern.h \
    ui/bargauge.h \
    ui/bartabsong.h \
    ui/barpatternbar.h

FORMS    += ui/barwindow.ui \
    ui/barsoundbar.ui \
    ui/bartabpattern.ui \
    ui/bargauge.ui \
    ui/bartabsong.ui \
    ui/barpatternbar.ui
