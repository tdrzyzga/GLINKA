#-------------------------------------------------
#
# Project created by QtCreator 2016-05-09T16:54:56
#
#-------------------------------------------------

QT       += core\
			gui\
			printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
			mainwindow/mainwindow.cpp \
			qcustomplot/qcustomplot.cpp \
			glinka2/glinka2.cpp \
			ratingwidget/ratingwidget.cpp \
			motor/motor.cpp \
			motorwidget/motorwidget.cpp \
			customplot/customplot.cpp \
			dialogrange/dialogrange.cpp \
    dialogcursorsbox/dialogcursorsbox.cpp

HEADERS  += mainwindow/mainwindow.h \
            qcustomplot/qcustomplot.h \
			glinka2/glinka2.h \
			ratingwidget/ratingwidget.h \
			motor/motor.h \
			motorwidget/motorwidget.h \
			customplot/customplot.h \
			dialogrange/dialogrange.h \
    dialogcursorsbox/dialogcursorsbox.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc



