#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T22:01:45
#
#-------------------------------------------------
QMAKE_LFLAGS += /INCREMENTAL:NO

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpaceShooter
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    player.cpp \
    enemy.cpp \
    projectile.cpp

HEADERS  += \
    game.h \
    player.h \
    enemy.h \
    projectile.h

RESOURCES += \
    resources.qrc
