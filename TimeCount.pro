#-------------------------------------------------
#
# Project created by QtCreator 2017-12-25T17:13:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimeCounter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG+=precompile_header
PRECOMPILED_HEADER = mainwindow.h

RESOURCES +=

RC_FILE=logo.rc
