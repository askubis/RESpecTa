#-------------------------------------------------
#
# Project created by QtCreator 2011-03-03T12:48:05
#
#-------------------------------------------------
CONFIG  += qt
QT       += core gui xml

TARGET = RESpecTa
TEMPLATE = app


SOURCES += main.cpp\
        respecta.cpp \
    diagramscene.cpp \
    editWidget.cpp \
    stateWidget.cpp \
    transWidget.cpp \
    StateTypeWidgets.cpp \
    baseState.cpp \
    Transition.cpp \
    TransDialog.cpp \
    Model.cpp \
    subtaskDialog.cpp \
    TreeModel.cpp \
    TreeItem.cpp \
    States.cpp

HEADERS  += respecta.h \
    diagramscene.h \
    Transition.h \
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
    StateTypeWidgets.h \
    baseState.h \
    Model.h \
    TransDialog.h \
    subtaskDialog.h \
    TreeModel.h \
    TreeItem.h \
    myTreeView.h \
    robotInit.h


FORMS    += respecta.ui

RESOURCES   =	diagramscene.qrc
