#-------------------------------------------------
#
# Project created by QtCreator 2016-07-07T13:01:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = packet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    capture.cpp \
    capturethread.cpp \
    packetdata.cpp

HEADERS  += mainwindow.h \
    capturethread.h \
    packetdata.h
LIBS += -L/usr/include/pcap
LIBS += -lpcap
INCLUDEPATH += /usr/include/pcap
DEPENDPATH += /usr/include/pcap
FORMS    += mainwindow.ui
