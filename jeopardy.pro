#-------------------------------------------------
# Project created by QtCreator 2011-11-20T15:01:54
# -------------------------------------------------
QT += xml \
    widgets \
    xmlpatterns \
    gui \
    multimedia \
    phonon4qt5
TARGET = jeopardy
TEMPLATE = app
CONFIG += no_lflags_merge
SOURCES += main.cpp \
    jeopardy.cpp \
    player.cpp \
    gamefield.cpp \
    answer.cpp \
    editor.cpp \
    podium.cpp \
    doublejeopardy.cpp
HEADERS += jeopardy.h \
    player.h \
    gamefield.h \
    answer.h \
    editor.h \
    podium.h \
    doublejeopardy.h
FORMS += answer.ui
