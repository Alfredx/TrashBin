#-------------------------------------------------
#
# Project created by QtCreator 2013-03-25T13:33:22
#
#-------------------------------------------------

CONFIG   += qaxcontainer
QT       += core gui\
#            axcontainer


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calendar
TEMPLATE = app

#LIBS += -lQt5AxServer \
#-lQt5AxContainer

SOURCES += main.cpp\
        mainwindow.cpp \
    excel.cpp \
    calendar.cpp \
    calendarunittest.cpp

HEADERS  += mainwindow.h \
    excel.h \
    calendar.h \
    calendarunittest.h

FORMS    += mainwindow.ui
