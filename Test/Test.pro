#-------------------------------------------------
#
# Project created by QtCreator 2017-03-23T09:45:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    password.cpp \
    admin.cpp \
    ad.cpp \
    field.cpp \
    addeditquestion.cpp \
    sual.cpp \
    exam.cpp \
    identity.cpp \
    encryption.cpp \
    result.cpp

HEADERS  += mainwindow.h \
    password.h \
    admin.h \
    ad.h \
    field.h \
    addeditquestion.h \
    sual.h \
    exam.h \
    identity.h \
    encryption.h \
    result.h

FORMS    += mainwindow.ui \
    password.ui \
    admin.ui \
    ad.ui \
    addeditquestion.ui \
    exam.ui \
    identity.ui \
    result.ui

QMAKE_CXXFLAGS += -std=c++11
