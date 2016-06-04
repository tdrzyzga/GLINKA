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
           glinka/glinka.cpp \
           qcustomplot/qcustomplot.cpp

HEADERS  += mainwindow/mainwindow.h \
            glinka/glinka.h \
            qcustomplot/qcustomplot.h \

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc



