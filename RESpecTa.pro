#-------------------------------------------------
#
# Project created by QtCreator 2011-03-03T12:48:05
#
#-------------------------------------------------

QT       += core gui

TARGET = RESpecTa
TEMPLATE = app


SOURCES += main.cpp\
        respecta.cpp \
    diagramscene.cpp \
    diagramtextitem.cpp \
    editWidget.cpp \
    stateWidget.cpp \
    transWidget.cpp \
    GraphFunctions.cpp \
    StateTypeWidgets.cpp \
    baseState.cpp \
    Transition.cpp

HEADERS  += respecta.h \
    diagramscene.h \
    Transition.h \
    diagramtextitem.h \
    Graph.h \
    globals.h \
    Coordinates.h \
    Pose.h \
    sysInitNode.h \
    RobotSet.h \
    States.h \
    editWidget.h \
    stateWidget.h \
    transWidget.h \
    GraphFunctions.h \
    StateTypeWidgets.h \
    baseState.h \
    StateEditDialog.h

FORMS    += respecta.ui

RESOURCES   =	diagramscene.qrc
