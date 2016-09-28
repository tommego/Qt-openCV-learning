#-------------------------------------------------
#
# Project created by QtCreator 2016-09-27T19:13:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BlurEffect
TEMPLATE = app

include(../Widgets/Widgets.pri)

PKGCONFIG += opencv
CONFIG += c++11 link_pkgconfig
SOURCES += main.cpp \
    blurwidget.cpp

HEADERS  += \
    blurwidget.h
