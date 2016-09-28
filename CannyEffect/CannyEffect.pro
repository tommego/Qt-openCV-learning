#-------------------------------------------------
#
# Project created by QtCreator 2016-09-27T18:34:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CannyEffect
TEMPLATE = app

include(../Widgets/Widgets.pri)

PKGCONFIG += opencv
CONFIG += c++11 link_pkgconfig
SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h
