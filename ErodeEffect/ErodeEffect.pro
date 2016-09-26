#-------------------------------------------------
#
# Project created by QtCreator 2016-09-26T21:44:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../Widgets/Widgets.pri)

TARGET = ErodeEffect
TEMPLATE = app

PKGCONFIG += opencv
CONFIG += c++11 link_pkgconfig



SOURCES += main.cpp

HEADERS  +=
