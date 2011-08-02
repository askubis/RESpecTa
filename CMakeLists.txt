# Try to find and setup Qt4 for this project
FIND_PACKAGE(Qt4)

IF(QT_FOUND)

MESSAGE(STATUS "\tUsing Qt ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH} (${QT_QMAKE_EXECUTABLE})")
MESSAGE(STATUS "\tIncludes in ${QT_INCLUDE_DIR}")

# add Qt modules here, the include will setup QT_LIBRARIES
#
# SET(QT_USE_XXX TRUE)
#
# Possible values are:
# QT_DONT_USE_QTCORE
# QT_DONT_USE_QTGUI
# QT_USE_QT3SUPPORT
# QT_USE_QTASSISTANT
# QT_USE_QAXCONTAINER
# QT_USE_QAXSERVER
# QT_USE_QTDESIGNER
# QT_USE_QTMOTIF
# QT_USE_QTMAIN
# QT_USE_QTNETWORK
# QT_USE_QTNSPLUGIN
# QT_USE_QTOPENGL
# QT_USE_QTSQL
SET(QT_USE_QTXML TRUE)
# QT_USE_QTSVG
# QT_USE_QTTEST
# QT_USE_QTUITOOLS
# QT_USE_QTDBUS
# QT_USE_QTSCRIPT
# QT_USE_QTASSISTANTCLIENT
# QT_USE_QTHELP
# QT_USE_QTWEBKIT
# QT_USE_QTXMLPATTERNS
# QT_USE_PHONON

INCLUDE(${QT_USE_FILE})

# Include current directory, necessary for proper UI headers to work
#include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Source files
SET(GUI_CXX_SRCS
baseState.cpp
diagramscene.cpp
editWidget.cpp
main.cpp
Model.cpp
respecta.cpp
States.cpp
StateTypeWidgets.cpp
stateWidget.cpp
subtaskWidget.cpp
TransDialog.cpp
Transition.cpp
transWidget.cpp
TreeItem.cpp
TreeModel.cpp
)

# Class headers that have to be MOCed (i.e. classes derived from QObject)
SET(GUI_MOC_SRCS
baseState.h
Coordinates.h
diagramscene.h
editWidget.h
globals.h
Graph.h
Model.h
myTreeView.h
Pose.h
respecta.h
robotInit.h
RobotSet.h
StateEditDialog.h
States.h
StateTypeWidgets.h
stateWidget.h
subtaskWidget.h
TransDialog.h
Transition.h
transWidget.h
TreeItem.h
TreeModel.h
)

# Generate MOC files
QT4_WRAP_CPP(GUI_CXX_SRCS ${GUI_MOC_SRCS})

# UI files
SET(GUI_UI
respecta.ui
)

# Generate UI include files
QT4_WRAP_UI(GUI_CXX_SRCS ${GUI_UI})

QT4_ADD_RESOURCES(GUI_CXX_SRCS diagramscene.qrc)

# Create GUI executable
ADD_EXECUTABLE(RESpecTa ${GUI_CXX_SRCS})



#SET_TARGET_PROPERTIES(discode_gui PROPERTIES
#   BUILD_WITH_INSTALL_RPATH ON
#   INSTALL_RPATH_USE_LINK_PATH 1
#   INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib
#)
#
#install(
#  TARGETS discode_gui
#  RUNTIME DESTINATION bin COMPONENT applications
#)


ELSE(QT_FOUND)

    MESSAGE("Qt not found! GUI will not be built")

ENDIF(QT_FOUND)
