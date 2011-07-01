#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>

#include "States.h"
#include "Transition.h"

#ifndef GRAPH_H
#define GRAPH_H

using namespace boost;

struct state_t {
    typedef vertex_property_tag kind;
  };
struct transition_t {
    typedef edge_property_tag kind;
  };

typedef property<state_t, BaseState *> VertexProperty;
typedef property<transition_t, Transition *> EdgeProperty;

typedef adjacency_list<vecS, vecS, directedS, VertexProperty, EdgeProperty> MyGraphType;

typedef graph_traits<MyGraphType>::vertex_descriptor VertexType;
typedef graph_traits<MyGraphType>::edge_descriptor EdgeType;


#endif // GRAPH_H
