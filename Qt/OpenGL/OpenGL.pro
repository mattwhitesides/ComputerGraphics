#-------------------------------------------------
#
# Project created by QtCreator 2015-02-14T12:16:39
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GLWidget.cpp \
    Drawings.cpp

HEADERS  += mainwindow.h \
    GLWidget.h \
    Drawings.h

FORMS    += mainwindow.ui
