#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T22:01:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpaceShooter
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    player.cpp \
    enemy.cpp

HEADERS  += \
    game.h \
    player.h \
    enemy.h

RESOURCES += \
    resources.qrc
