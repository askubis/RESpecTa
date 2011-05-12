#include "Model.h"
//#include "GraphFunctions.cpp"

Model::Model()
{
    subtasks = new std::map<std::string, MyGraphType *>();
    mainName = "MAIN";
    subtasks->insert(std::make_pair(mainName, new MyGraphType()));
}

void Model::save(std::string filename)
{
    checkIfOK();

    for (std::map<std::string, MyGraphType *>::iterator it = subtasks->begin();it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if(((*it).first)==mainName)
        {
            printStates(tmp, std::string(filename.c_str()),true);
        }
        else
        {
            printStates(tmp, std::string((*it).first+".xml"), false);
        }
    }
}

void Model::deleteTransition(Transition * transition)
{
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if((findEdge(tmp, transition) )!=edges(*tmp).second)
            boost::remove_edge((*(findEdge(tmp, transition))), (*tmp));
    }
    transition->startItem()->removeTransition(transition);
    transition->endItem()->removeTransition(transition);
}

void Model::deleteState(BaseState * state)
{
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if((findVertex(tmp, state) )!=vertices(*tmp).second)
            boost::remove_vertex((*(findVertex(tmp, state))), (*tmp));
    }
}

bool Model::addState(BaseState * item, std::string subtaskName)
{
    if(item ==NULL)
    {
        res->getError(QString().fromStdString("A problem has been detected, code:\ntrying to insert NULL value").append(item->getName()));
    }
    if(!checkStateNameAvailable((*subtasks)[subtaskName],item->getName()))
    {
        res->getError(QString().fromStdString("This state already exists in the given subtask").append(item->getName()));
        return false;
    }

    boost::add_vertex(item, (*(*subtasks)[subtaskName]));
    return true;

}

bool Model::tryInsertTransition(Transition * line)
{
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if (((findVertex(tmp, line->startItem()) )!=vertices(*tmp).second) && ((findVertex(tmp, line->endItem()) )!=vertices(*tmp).second ))
        {
            boost::add_edge( (*(findVertex(tmp, line->startItem()))), (*(findVertex(tmp, line->endItem()))), line, (*tmp) );
            return true;
        }
    }
}

bool Model::checkNameAvailable(QString name)
{
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if (!checkStateNameAvailable(tmp, name))
        {
           return false;
        }
    }
    return true;
}

void Model::addSubtask(QString name)
{
    subtasks->insert(std::make_pair(name.toStdString(), new MyGraphType()));
}

QStringList Model::getTasksNameLists()
{
    QStringList subtaskList;
    for (std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end() ;it++)
    {
        subtaskList<<(*it).first.c_str();
    }
    return subtaskList;
}

QStringList Model::getTasksNameListsWithoutMain()
{
    QStringList subtaskList;
    for (std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end() ;it++)
    {
        if((*it).first!=mainName)subtaskList<<(*it).first.c_str();
    }
    return subtaskList;
}

QStringList Model::getAllStateNames(std::string sub)
{
    MyGraphType * tmp = (*subtasks)[sub];
    return getStateNames( (*tmp));
}


void Model::checkIfOK()
{
    char tab[200];
    //sprawdzic czy jest _init_ i _stop_ w głównym
    //sprawdzić czy jest _end_ w subtaskach
    //sprawdzić dla tranzycji czy subtask gdzieś istnieje
    //kazy stan poza end i stop musi miec przynajmniej jeden stan wyjsciowy

    //dla kazdego stanu tranzycje sa rozne//sprawdzac przy dodawaniu
    //czy graf spojny
    //czy z kazdego stanu da sie dojsc do end/stop
    MyGraphType * tmp = (*subtasks)[mainName];
    if( checkNameAvailable(QString("_init_"), tmp))
    {
        res->getError(QString().fromStdString("No INIT state in main task!"));
    }
    if(  checkNameAvailable(QString("_stop_"), tmp))
    {
        res->getError(QString().fromStdString("No STOP state in main task!"));
    }
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        if((*it).first==mainName) continue;
        MyGraphType * tmp2 = (*it).second;
        if ( checkNameAvailable(QString("_end_"), tmp2) )
        {
                std::string tmpSubName = (*it).first;
                sprintf(tab, "No END state in subtask: %s", tmpSubName.c_str());
                res->getError(QString().fromStdString(tab));
        }
    }

    typedef  property_map<MyGraphType, transition_t>::type TransitionMap;
    boost::graph_traits<MyGraphType>::edge_iterator startIt, endIt;
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        //std::cout<<(*it).first<<" "<<boost::num_vertices(*((*it).second))<<std::endl;
        //std::cout<<(*it).first<<" "<<boost::num_edges(*((*it).second))<<std::endl;

        TransitionMap transitionMap = get(transition_t(), (*((*it).second)));
        tie(startIt, endIt)=edges(*((*it).second));
        for(;startIt!=endIt;startIt++)
        {
            Transition * transition = boost::get(transitionMap, *startIt);
            if(transition->getSubtask() == "")continue;//no use to check
            bool exists= false;
            for(std::map<std::string, MyGraphType *>::iterator it2 = subtasks->begin(); it2!=subtasks->end();it2++)
            {
                if((*it).first==mainName) continue;
                if (!checkNameAvailable(QString().fromStdString(transition->getSubtask()), (*it2).second))
                {
                     exists = true;
                     break;
                }
            }
            if(!exists)
            {
                boost::graph_traits<MyGraphType>::vertex_descriptor u,v;
                u = source((*startIt), (*((*it).second)));
                v = target((*startIt), (*((*it).second)));
                BaseState * srcState;
                BaseState * destState;
                srcState = (BaseState *)u;
                destState = (BaseState *)v;

                sprintf(tab, "No state %s in any subtasks, and stated in a transition between %s, %s ", transition->getSubtask().c_str(), srcState->getName().toStdString().c_str(), destState->getName().toStdString().c_str());
                res->getError(QString().fromStdString("tab"));
            }
        }
        tmp = (*it).second;
        typedef  property_map<MyGraphType, state_t>::type StateMap;
        StateMap stateMap = get(state_t(), (*((*it).second)));
        boost::graph_traits<MyGraphType>::vertex_iterator first, last;
        tie(first, last) = vertices(*tmp);
        for(;first!=last;first++)
        {
            BaseState * state = boost::get(stateMap, *first);
            //std::cout<<state<<std::endl;
            //std::cout<<state->getName().toStdString()<<std::endl;
            if(state ==NULL)continue;
            boost::graph_traits<MyGraphType>::out_edge_iterator OEIt, OEIt2;
            tie(OEIt, OEIt2)=out_edges((*first), *tmp);
            if(OEIt==OEIt2)//no outgoing edges
            {
                //QString tmpQString = state->getName();
                //tmpQString.toLower();
                //std::string namestring = state->getName().toStdString();
                if(state->getName().toLower()!=QString().fromStdString("_end_") && state->getName().toLower()!=QString().fromStdString("_stop_"))
                {
                    QString tmpQstring = state->getName().append(QString().fromStdString( " state has no outgoing edges and should have at least 1"));
                    res->getError(tmpQstring);
                }
            }
            else
            {
                bool mark = false;
                for(;OEIt!=OEIt2;OEIt++)
                {
                    Transition * tr = boost::get(transitionMap, *OEIt);
                    if(tr->getCondition().toLower()=="true")
                        mark=true;
                    else
                        mark = false;
                }
                if(!mark)
                {
                    QString tmpQstring = state->getName().append(QString().fromStdString( " state should have last\nTransition with condition true"));
                    res->getError(tmpQstring);
                }
            }
        }

    }


}


bool Model::checkNameAvailable(QString name, MyGraphType * G)
{
    if (!checkStateNameAvailable( G, name))
    {
       return false;
    }
    return true;
}


std::string Model::getSubtaskName(QString StateName)
{
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if (!checkStateNameAvailable( tmp, StateName))
        {
           return (*it).first;
        }
    }
    return std::string("");
}

bool Model::ReplaceState(BaseState * oldState, BaseState * newState)
{
    //check if the state wasn't deleted
    std::string subtaskName = getSubtaskName(oldState->getName());
    if(subtaskName==std::string(""))
    {
        res->getError(QString().fromStdString("The state you were editing has been deleted,\nplease choose the insert option to insert the state"));
        return false;
    }
    MyGraphType * tmpGraph = (*subtasks)[subtaskName];
    typedef  property_map<MyGraphType, state_t>::type StateMap;
    StateMap stateMap = get(state_t(), (*(tmpGraph)));
    boost::graph_traits<MyGraphType>::vertex_iterator first =findVertex(tmpGraph, oldState);
    {//changing
        boost::put(stateMap, *first, newState);
        return true;
    }
    return false;


}


void Model::MoveTransitionUp(BaseState * st, int index)
{
    std::string subtaskName = getSubtaskName(st->getName());
    if(subtaskName==std::string(""))
    {
        res->getError(QString().fromStdString("The state you were editing has been deleted,\nplease choose the insert option to insert the state"));
        return;
    }

    MyGraphType * tmpGraph = (*subtasks)[subtaskName];
    boost::graph_traits<MyGraphType>::vertex_iterator first = findVertex(tmpGraph, st);

    typedef  property_map<MyGraphType, transition_t>::type TransitionMap;
    TransitionMap transitionMap = get(transition_t(), (*tmpGraph));
    Transition * transition;

    boost::graph_traits<MyGraphType>::out_edge_iterator startIt, endIt;
    tie(startIt, endIt)=out_edges((*first), (*tmpGraph));
    for (int i = 0 ;i<index-1 && startIt!=endIt;startIt++, i++)
    {
    }
    std::vector<Transition *> transVect;
    for (;startIt!=endIt;startIt++)
    {
        transition = boost::get(transitionMap, *startIt);
        transVect.push_back(transition);
    }
    for(int i =0;i<transVect.size(); i++)
    {
        boost::remove_edge((*(findEdge(tmpGraph, transVect[i]))), (*tmpGraph));
    }

    tryInsertTransition(transVect[1]);
    tryInsertTransition(transVect[0]);
    for(int i=2;i<transVect.size();i++)
        tryInsertTransition(transVect[i]);

}

void Model::MoveTransitionDown(BaseState * st, int index)
{
    std::string subtaskName = getSubtaskName(st->getName());
    if(subtaskName==std::string(""))
    {
        res->getError(QString().fromStdString("The state you were editing has been deleted,\nplease choose the insert option to insert the state"));
        return;
    }
    MyGraphType * tmpGraph = (*subtasks)[subtaskName];
    boost::graph_traits<MyGraphType>::vertex_iterator first = findVertex(tmpGraph, st);

    boost::graph_traits<MyGraphType>::out_edge_iterator startIt, endIt;
    tie(startIt, endIt)=out_edges((*first), (*tmpGraph));
    for (int i = 0 ;i<index && startIt!=endIt;startIt++, i++)
    {
    }
    typedef  property_map<MyGraphType, transition_t>::type TransitionMap;
    TransitionMap transitionMap = get(transition_t(), (*tmpGraph));
    Transition * transition;

    std::vector<Transition *> transVect;
    for (;startIt!=endIt;startIt++)
    {
        transition = boost::get(transitionMap, *startIt);
        transVect.push_back(transition);
    }
    for(int i =0;i<transVect.size(); i++)
    {
        boost::remove_edge((*(findEdge(tmpGraph, transVect[i]))), (*tmpGraph));
    }
    tryInsertTransition(transVect[1]);
    tryInsertTransition(transVect[0]);
    for(int i=2;i<transVect.size();i++)
        tryInsertTransition(transVect[i]);
}

std::vector<Transition *> Model::getTransitions(BaseState * st)
{
    std::vector<Transition *> tranVect;
    std::string subtaskName = getSubtaskName(st->getName());
    if(subtaskName==std::string(""))
    {
        res->getError(QString().fromStdString("The state you were editing has been deleted,\nplease choose the insert option to insert the state"));
        return tranVect;
    }
    MyGraphType * tmpGraph = (*subtasks)[subtaskName];
    boost::graph_traits<MyGraphType>::vertex_iterator first = findVertex(tmpGraph, st);

    boost::graph_traits<MyGraphType>::out_edge_iterator startIt, endIt;
    tie(startIt, endIt)=out_edges((*first), (*tmpGraph));
    typedef  property_map<MyGraphType, transition_t>::type TransitionMap;
    TransitionMap transitionMap = get(transition_t(), (*tmpGraph));
    for (; startIt!=endIt;startIt++)
    {
        Transition * transition = boost::get(transitionMap, *startIt);
        tranVect.push_back(transition);
    }
    return tranVect;
}

bool Model::checkTransitonExists(Transition * trans)
{
    for (std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end() ;it++)
    {
        MyGraphType * tmpGraph = (*it).second;
        if(findEdge(tmpGraph,trans)!= edges(*tmpGraph).second) return true;
    }
    return false;
}

boost::graph_traits<MyGraphType>::edge_iterator Model::findEdge ( MyGraphType * graph, Transition * toFind)
{
    property_map<MyGraphType, transition_t>::type Trans = get(transition_t(), (*graph));
    graph_traits<MyGraphType>::edge_iterator first, last;
    tie(first, last) = edges(*graph);
    for ( ;first!=last; first++)
    if ( boost::get(Trans, (*first)) == toFind) return first;
    return last;
}

boost::graph_traits<MyGraphType>::vertex_iterator Model::findVertex ( MyGraphType * graph, BaseState * toFind)
{
    property_map<MyGraphType, state_t>::type State = get(state_t(), (*graph));
    graph_traits<MyGraphType>::vertex_iterator first, last;
    tie(first, last) = vertices(*graph);
    for ( ;first!=last; first++)
    if ( boost::get(State, (*first)) == toFind) return first;
    return last;
}




void Model::printStates(MyGraphType *G, std::string FileName, bool ifMain)
{
    boost::graph_traits<MyGraphType>::vertex_iterator first,last;
    tie(first, last) = vertices(*G);
    QFile* file = new QFile(QString().fromStdString(FileName));
    file->open( QIODevice::WriteOnly);
    QXmlStreamWriter * writer = new QXmlStreamWriter(file);
    writer->setAutoFormatting(1);
    writer->setCodec("UTF-8");
    writer->writeStartDocument("1.0");
    writer->writeDTD(QString().fromStdString("<!DOCTYPE TaskDescription SYSTEM \"fsautomat.dtd\" >"));

    typedef  property_map<MyGraphType, state_t>::type StateMap;
    StateMap stateMap = get(state_t(), *G);

    typedef  property_map<MyGraphType, transition_t>::type TransitionMap;
    TransitionMap transitionMap = get(transition_t(), *G);

    BaseState *State;
    Transition * transition;

    writer->writeStartElement("TaskDescription");
    for (;first != last;first++)
    {
      State = boost::get(stateMap, *first);
      writer->writeStartElement("State");
      writer->writeAttribute(QString("id"), State->getName());
      writer->writeAttribute(QString("type"), QString().fromStdString(STATE_TYPE_TABLE[State->getType()]));
      char tab[20];
      sprintf(tab, "%lf", State->pos().x());
      writer->writeTextElement("PosX", QString().fromStdString(tab));
      sprintf(tab, "%lf", State->pos().y());
      writer->writeTextElement("PosY", QString().fromStdString(tab));


      State->Print(writer);


      boost::graph_traits<MyGraphType>::out_edge_iterator startIt, endIt;
      tie(startIt, endIt)=out_edges((*first), *G);
      for ( ;startIt!=endIt;startIt++)
      {
          transition = boost::get(transitionMap, *startIt);
          writer->writeStartElement("Transition");
          writer->writeAttribute("condition", transition->getCondition());
          boost::graph_traits<MyGraphType>::vertex_descriptor u;
          u = target((*startIt), *G);
          BaseState *tmpState;
          tmpState = boost::get(stateMap, u);
          QString tmpString;
          if(transition->getSubtask() != "")
          {
                tmpString.fromStdString(transition->getSubtask()).append(QString(">>")).append(QString(tmpState->getName()));
          }
          else
          {
              tmpString= QString(tmpState->getName());
          }
          writer->writeAttribute("target", tmpString);

          writer->writeEndElement();
      }

      writer->writeEndElement();

    }


    if(ifMain)
    {
        for (std::map<std::string, MyGraphType *>::iterator it = subtasks->begin();it!=subtasks->end();it++)
        {
            if((*it).first == mainName)continue;
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

}



QStringList Model::getStateNames(MyGraphType G)
{
    boost::graph_traits<MyGraphType>::vertex_iterator first,last;
    tie(first, last) = vertices(G);
    QStringList items;

    typedef  property_map<MyGraphType, state_t>::type StateMap;
    StateMap stateMap = get(state_t(), G);

       //typedef  property_traits<StateMap>::value_type StateType;
       //StateType st;
       BaseState * x;

       while (first != last)
       {
         x = boost::get(stateMap, *first);
         //x = (BaseState *)st;
         QString tmp = x->getName();
         items<< (tmp);
         ++first;
       }
       return items;
}


bool Model::checkStateNameAvailable(MyGraphType *G, QString given)
{
    boost::graph_traits<MyGraphType>::vertex_iterator first,last;
    tie(first, last) = vertices(*G);

    typedef  property_map<MyGraphType, state_t>::type StateMap;
    StateMap stateMap = get(state_t(), *G);

    BaseState * x;

       while (first != last)
       {
           QString GivenLow = given.toLower();
         x = boost::get(stateMap, *first);
         QString tmp = x->getName().toLower();
         if (tmp==GivenLow) return false;
         ++first;
       }
       return true;
}






