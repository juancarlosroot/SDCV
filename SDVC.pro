#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T23:42:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SDVC
TEMPLATE = app

QT_CONFIG -= no-pkg-config
CONFIG  += link_pkgconfig
PKGCONFIG += opencv

SOURCES += main.cpp\
        mainwindow.cpp\
        player.cpp \
        controller/blob.cpp \
    controller/bloblist.cpp \
    controller/roi.cpp \
    controller/drawing.cpp \
    controller/clasifier.cpp \
    controller/detector.cpp \
    controller/munkres.cpp \
    controller/track.cpp \
    controller/tracker.cpp

HEADERS  += mainwindow.h\
        player.h \
        controller/blob.h \
    controller/bloblist.h \
    controller/roi.h \
    controller/drawing.h \
    controller/clasifier.h \
    controller/detector.h \
    controller/munkres.h \
    controller/track.h \
    controller/tracker.h

FORMS    += mainwindow.ui

RESOURCES += \
    sdvc.qrc
