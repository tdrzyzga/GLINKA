#-------------------------------------------------
#
# Project created by QtCreator 2016-05-09T16:54:56
#
#-------------------------------------------------

QT       += core gui\
                        printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow/mainwindow.cpp \
           qcustomplot/qcustomplot.cpp \
    glinka2.cpp

HEADERS  += mainwindow/mainwindow.h \
            qcustomplot/qcustomplot.h \
    glinka2.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc



