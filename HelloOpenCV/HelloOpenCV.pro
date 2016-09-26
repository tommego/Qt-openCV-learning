#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T14:32:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloOpenCV
TEMPLATE = app

PKGCONFIG += opencv
CONFIG += c++11 link_pkgconfig


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h
