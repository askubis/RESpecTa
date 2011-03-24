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
    diagramitem.cpp \
    diagramtextitem.cpp \
    arrow.cpp \
    StateEditDialog.cpp \
    editWidget.cpp \
    stateWidget.cpp \
    transWidget.cpp \
    GraphFunctions.cpp

HEADERS  += respecta.h \
    diagramscene.h \
    diagramitem.h \
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
    GlobalVariables.h

FORMS    += respecta.ui

RESOURCES   =	diagramscene.qrc
