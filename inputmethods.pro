#-------------------------------------------------
#
# Project created by QtCreator 2016-08-16T17:03:50
#
#-------------------------------------------------

QT       += core gui webenginewidgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = inputmethods
TEMPLATE = app


SOURCES += \
    colorpicker.cpp \
    controlview.cpp \
    main.cpp \
    mainwindow.cpp \
    referenceview.cpp \
    testview.cpp \
    webview.cpp

HEADERS  += \
    colorpicker.h \
    controlview.h \
    mainwindow.h \
    referenceview.h \
    testview.h \
    webview.h

RESOURCES += \
    test.qrc

DISTFILES += \
    testdata.csv
