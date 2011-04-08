#include "GraphFunctions.h"
#include "baseState.h"
//#include "baseState.cpp"
#include <QtGui>


using namespace boost;
using namespace std;

template <class VertexIter, class theGraph>
QStringList getStateNames(VertexIter first, VertexIter last, const theGraph &G)
{
    QStringList items;
    typedef typename property_map<theGraph, state_t>::const_type StateMap;
       StateMap stateMap = get(state_t(), G);

       typedef typename property_traits<StateMap>::value_type StateType;
       StateType st;
       //BaseState x;

       while (first != last)
       {
         st = boost::get(stateMap, *first);
         std::string tmp = st.getName();
         //std::string tmp = x.getName();
         items<< (tmp.c_str());
         ++first;
       }
       return items;
}


template <class VertexIter, class theGraph>
void printStates(VertexIter first, VertexIter last, const theGraph &G, std::string FileName)
{
    typedef typename property_map<theGraph, state_t>::const_type StateMap;
       StateMap stateMap = get(state_t(), G);


       typedef typename property_map<theGraph, transition_t>::const_type TransitionMap;
          TransitionMap transitionMap = get(transition_t(), G);

       //typedef typename property_traits<StateMap>::value_type StateType;
       //StateType st;

       BaseState *State;
       Transition * transition;
       std::ofstream f(FileName.c_str());
       while (first != last)
       {
         State = boost::get(stateMap, *first);
         f<<State->Print();
         f<<"\n";

         //boost::graph_traits<MyGraphType>::vertex_iterator iter;
         //iter.
         boost::graph_traits<MyGraphType>::out_edge_iterator startIt, endIt;
         tie(startIt, endIt)=out_edges((*first), G);
         for ( ;startIt!=endIt;startIt++)
         {
             transition = boost::get(transitionMap, *startIt);
             f<<transition->Print();
             boost::graph_traits<MyGraphType>::vertex_descriptor u;
             u = target((*startIt), G);
             BaseState *tmpState;
             tmpState = boost::get(stateMap, u);
             f<<"\nDestination State :";
             f<<tmpState->getName();
             f<<"\n";

         }
         f<<"\n";
         ++first;
       }
       f.close();

}


boost::graph_traits<MyGraphType>::vertex_iterator findVertex ( MyGraphType * graph, BaseState * toFind)
{
    property_map<MyGraphType, state_t>::type State = get(state_t(), (*graph));
    graph_traits<MyGraphType>::vertex_iterator first, last;
    tie(first, last) = vertices(*graph);
    for ( ;first!=last; first++)
    if ( boost::get(State, (*first)) == toFind) return first;
    return last;
}


boost::graph_traits<MyGraphType>::edge_iterator findEdge ( MyGraphType * graph, Transition * toFind)
{
    property_map<MyGraphType, transition_t>::type Trans = get(transition_t(), (*graph));
    graph_traits<MyGraphType>::edge_iterator first, last;
    tie(first, last) = edges(*graph);
    for ( ;first!=last; first++)
    if ( boost::get(Trans, (*first)) == toFind) return first;
    return last;
}




