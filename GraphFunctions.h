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

#include <fstream>
//#include "Graph.h"


#ifndef GRAPHFUNCTIONS_H
#define GRAPHFUNCTIONS_H



template <class VertexIter, class theGraph>
QStringList getStateNames(VertexIter first, VertexIter last, const theGraph &G);

template <class VertexIter, class theGraph>
void printStates(VertexIter first, VertexIter last, const theGraph &G, std::string fileName);



template <class VertexIter, class theGraph>
bool checkStateNameAvailable(VertexIter first, VertexIter last, const theGraph &G);



boost::graph_traits<MyGraphType>::vertex_iterator findVertex ( MyGraphType * graph, BaseState * toFind);

boost::graph_traits<MyGraphType>::edge_iterator findEdge ( MyGraphType * graph, Transition * toFind);






#endif // GRAPHFUNCTIONS_H
