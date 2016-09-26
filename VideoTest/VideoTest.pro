#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T15:06:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoTest
TEMPLATE = app
include(../Widgets/Widgets.pri)

PKGCONFIG += opencv
CONFIG += c++11 link_pkgconfig


SOURCES += main.cpp

HEADERS  +=
