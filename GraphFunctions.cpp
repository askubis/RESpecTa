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
         QString tmp = st.getName();
         //QString tmp = x.getName();
         items<< (tmp);
         ++first;
       }
       return items;
}

template <class VertexIter, class theGraph>
bool checkStateNameAvailable(VertexIter first, VertexIter last, const theGraph &G, QString given)
{
    typedef typename property_map<theGraph, state_t>::const_type StateMap;
       StateMap stateMap = get(state_t(), G);

       typedef typename property_traits<StateMap>::value_type StateType;
       StateType st;

       while (first != last)
       {
         st = boost::get(stateMap, *first);
         QString tmp = st->getName();
         if (tmp==given) return false;
         ++first;
       }
       return true;
}


template <class VertexIter, class theGraph>
        void printStates(VertexIter first, VertexIter last, const theGraph &G, std::string FileName, std::map<std::string, MyGraphType *> * subtasks)
{
    QFile* file = new QFile(QString().fromStdString(FileName));
    file->open( QIODevice::WriteOnly);
    QXmlStreamWriter * writer = new QXmlStreamWriter(file);
    writer->setAutoFormatting(1);
    writer->setCodec("UTF-8");
    writer->writeStartDocument("1.0");
    writer->writeDTD(QString().fromStdString("<!DOCTYPE TaskDescription SYSTEM \"fsautomat.dtd\" >"));

    typedef typename property_map<theGraph, state_t>::const_type StateMap;
    StateMap stateMap = get(state_t(), G);

    typedef typename property_map<theGraph, transition_t>::const_type TransitionMap;
    TransitionMap transitionMap = get(transition_t(), G);

    BaseState *State;
    Transition * transition;

    //test



//make some enterance to the file
//get to know what is the routine of file adding (subtasks)
    writer->writeStartElement("TaskDescription");
    for (;first != last;first++)
    {
      State = boost::get(stateMap, *first);
      writer->writeStartElement("State");
      writer->writeAttribute(QString("id"), State->getName());
      writer->writeAttribute(QString("type"), QString().fromStdString(STATE_TYPE_TABLE[State->getType()]));
      State->Print(writer);


      boost::graph_traits<MyGraphType>::out_edge_iterator startIt, endIt;
      tie(startIt, endIt)=out_edges((*first), G);
      for ( ;startIt!=endIt;startIt++)
      {
          transition = boost::get(transitionMap, *startIt);
          writer->writeStartElement("Transition");
          writer->writeAttribute("condition", transition->getCondition());
          boost::graph_traits<MyGraphType>::vertex_descriptor u;
          u = target((*startIt), G);
          BaseState *tmpState;
          tmpState = boost::get(stateMap, u);
          QString * tmp= new QString(tmpState->getName());
          if(transition->getSubtask())
          {

          }
          writer->writeAttribute("target", *tmp);

          writer->writeEndElement();
      }

      writer->writeEndElement();

    }


    if(subtasks!=NULL)
    {
        for (std::map<std::string, MyGraphType *>::iterator it = subtasks->begin();it!=subtasks->end();it++)
        {
            std::string subtaskFileName = (*it).first + ".xml";
            writer->writeStartElement("xi:include");
            writer->writeAttribute("href", QString().fromStdString(subtaskFileName));
            writer->writeAttribute("parse", "xml");
            writer->writeAttribute("xmlns:xi", "http://www.w3.org/2001/XInclude");
        }
    }
    writer->writeEndElement();
    writer->writeEndDocument();
    file->close();



    /*typedef typename property_map<theGraph, state_t>::const_type StateMap;
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
             f<<tmpState->getName().toStdString();
             f<<"\n";

         }
         f<<"\n";
         ++first;
       }
       f.close();//*/

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




