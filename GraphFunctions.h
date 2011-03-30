#include "Graph.h"
#include "globals.h"
#include "States.h"
#include "baseState.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


#include <QDialog>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QGridLayout;
class QVBoxLayout;
QT_END_NAMESPACE

#include <QtGui>


#ifndef GRAPHFUNCTIONS_H
#define GRAPHFUNCTIONS_H



template <class VertexIter, class theGraph>
QStringList getStateNames(VertexIter first, VertexIter last, const theGraph &G);





#endif // GRAPHFUNCTIONS_H
