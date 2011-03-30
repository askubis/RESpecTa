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




