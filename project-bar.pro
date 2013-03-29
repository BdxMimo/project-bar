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
    ui/barpatternbar.cpp \
    ui/barsongtimeline.cpp \
    ui/barsongarea.cpp \
    ui/barpatternbarscrollareacontents.cpp \
    ui/barsongareaview.cpp \
    ui/barsongareascene.cpp \
    ui/barexportdialog.cpp


HEADERS  += src/barwindow.h \
    ui/barsoundbar.h \
    ui/bartabpattern.h \
    ui/bargauge.h \
    ui/bartabsong.h \
    ui/barpatternbar.h \
    ui/barsongtimeline.h \
    ui/barsongarea.h \
    ui/barpatternbarscrollareacontents.h \
    ui/barsongareaview.h \
    ui/barsongareascene.h \
    ui/barexportdialog.h


SOURCES += BARSox/BARSoxTrack.cpp \
    BARSox/BARSoxBufferPos.cpp \
    BARSox/BARSoxPatternSoundSystem.cpp

HEADERS += BARSox/BARSoxTrack.h \
    BARSox/BARSoxNode.h \
    BARSox/BARSoxPositionNode.h \
    BARSox/BARSoxBufferPos.h \
    BARSox/BARSoxPatternSoundSystem.h \
    BARSox/BARSimpleResampler.h \
    BARSox/BARDefines.h

win32 {
LIBS += -LC:/Sox/sox-14.4.1rc3/src/.libs -llibsox
INCLUDEPATH += C:/Sox/sox-14.4.1rc3/src/
}

FORMS    += ui/barwindow.ui \
    ui/barsoundbar.ui \
    ui/bartabpattern.ui \
    ui/bargauge.ui \
    ui/bartabsong.ui \
    ui/barpatternbar.ui \
    ui/barsongtimeline.ui \
    ui/barsongarea.ui \
    ui/barpatternbarscrollareacontents.ui \
    ui/barexportdialog.ui

RESOURCES += \
    images.qrc
