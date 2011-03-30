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
    arrow.cpp \
    StateEditDialog.cpp \
    editWidget.cpp \
    stateWidget.cpp \
    transWidget.cpp \
    GraphFunctions.cpp \
    StateTypeWidgets.cpp \
    baseState.cpp

HEADERS  += respecta.h \
    diagramscene.h \
    arrow.h \
    diagramtextitem.h \
    Graph.h \
    globals.h \
    Transition.h \
    Coordinates.h \
    Pose.h \
    sysInitNode.h \
    RobotSet.h \
    States.h \
    StateEditDialog.h \
    editWidget.h \
    stateWidget.h \
    transWidget.h \
    GraphFunctions.h \
    GlobalVariables.h \
    StateTypeWidgets.h \
    baseState.h

FORMS    += respecta.ui

RESOURCES   =	diagramscene.qrc
