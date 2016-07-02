#-------------------------------------------------
#
# Project created by QtCreator 2016-06-28T16:42:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ShittyGUi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    additivedictionarybin.cpp \
    additivedictionaryhash.cpp \
    additivedictionaryhtc.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    adword.h \
    bintree.h \
    hash.h \
    htchained.h \
    additivedictionarybin.h \
    additivedictionaryhash.h \
    additivedictionaryhtc.h

FORMS    += mainwindow.ui
