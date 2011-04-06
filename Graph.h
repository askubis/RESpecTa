#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>

#include "States.h"
#include "arrow.h"

#ifndef GRAPH_H
#define GRAPH_H

using namespace boost;
using namespace std;

struct state_t {
    typedef vertex_property_tag kind;
  };
struct transition_t {
    typedef edge_property_tag kind;
  };
/*struct graph_title_t{
    typedef graph_property_tag kind;
};*/

typedef property<state_t, BaseState> VertexProperty;
typedef property<transition_t, Transition> EdgeProperty;
//typedef property<graph_title_t, std::string> GraphProperty;

//typedef adjacency_list<listS, listS, directedS, VertexProperty, EdgeProperty, GraphProperty> MyGraphType;
typedef adjacency_list<vecS, vecS, directedS, VertexProperty, EdgeProperty> MyGraphType;








#endif // GRAPH_H
