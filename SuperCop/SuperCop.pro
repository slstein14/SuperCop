#-------------------------------------------------
#
# Project created by QtCreator 2015-04-07T20:48:38
#
#-------------------------------------------------

QT       += core gui quick declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuperCop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controls.cpp \
    contactus.cpp \
    highscores.cpp \
    supercopgame.cpp \
    player.cpp \
    enemy.cpp \
    levelbase.cpp \
    donut.cpp \
    platform.cpp \
    wall.cpp

HEADERS  += mainwindow.h \
    controls.h \
    contactus.h \
    highscores.h \
    supercopgame.h \
    player.h \
    enemy.h \
    levelbase.h \
<<<<<<< HEAD
    donut.h \
    platform.h \
    wall.h
=======
    donut.h
>>>>>>> c7d8bfb50a85e9275b0bd1e9d623e110e09ec278

FORMS    += mainwindow.ui \
    controls.ui \
    contactus.ui \
    highscores.ui \
    supercopgame.ui

DISTFILES +=
