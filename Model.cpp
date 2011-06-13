#include "Model.h"
//#include "GraphFunctions.cpp"




//TODO:
//change filenames while saving and loading - need to have folderPath+=filename

Model::Model()
{
    subtasks = new std::map<std::string, MyGraphType *>();
    mainName = "MAIN";
    subtasks->insert(std::make_pair(mainName, new MyGraphType()));
}

void Model::save(QString myFile)
{
    std::string filename = myFile.toStdString();
myFile.chop(4);
QString logPath =SaveFolder+ myFile;
logPath.append(".log");
int ind = myFile.lastIndexOf('/');
myFile.remove(0,ind+1);
std::cout<<"SAVE1: "<<myFile.toStdString()<<std::endl;

    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin();it!=subtasks->end();it++)
    {
        if((*it).first==mainName)continue;

        if(myFile==QString().fromStdString((*it).first) )
        {
            res->getError(QString("a subtask exists with a name you wanted to\nsave your graph with, choose other filename"));
            res->clearSaveName();
            return;
        }
    }


   if(myFile.toStdString()!=mainName)
   {
     subtasks->insert(std::make_pair(myFile.toStdString(), (*subtasks)[mainName]));
     subtasks->erase(mainName);
     mainName = myFile.toStdString();
   }


    QStringList errors = checkIfOK();
    if(errors.size()==0)
    {

    }
    else if (errors.size()<=5)
    {
        foreach(QString x, errors)
        {
            res->getError(x);
        }
    }
    else
    {
        char tab[200];
        sprintf(tab, "There were %d errors while saving,\nto see them please see the log:\n%s", errors.size(), logPath.toStdString().c_str());
        res->getError(QString(tab));
        QFile file(logPath.toStdString().c_str());
        if(!file.open(QIODevice::WriteOnly))
            qDebug()<<"Error opening the file";
        QTextStream streamToWrite(&file);
        foreach(QString x, errors)
        {
            const char* test = x.toStdString().c_str();
            streamToWrite<<test;
            streamToWrite<<"\n";
        }
        file.close();

    }

    for (std::map<std::string, MyGraphType *>::iterator it = subtasks->begin();it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if(((*it).first)==mainName)
        {
            if(!myFile.endsWith(".xml"))
            {
                myFile.append(QString(".xml"));
            }
            printStates(tmp, std::string(myFile.toStdString()),true);
        }
        else
        {
            printStates(tmp, std::string((*it).first+".xml"), false);
        }
    }
    return;
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
        res->getError(QString("A problem has been detected, code:\ntrying to insert NULL value").append(item->getName()));
    }
    if(!checkStateNameAvailable((*subtasks)[subtaskName],item->getName()))
    {
        res->getError(QString( "This state already exists in the given subtask").append(item->getName()));
        return false;
    }

    boost::add_vertex(item, (*(*subtasks)[subtaskName]));
    return true;

}

bool Model::checkTransCondAvailabe(Transition * line,QString cond)
{
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if (findEdge(tmp, line)!=edges(*tmp).second)
        {
            boost::graph_traits<MyGraphType>::out_edge_iterator OEIt, OEIt2;
            tie(OEIt, OEIt2)=out_edges((*(findVertex(tmp, line->startItem()))), *tmp);
            for(;OEIt!=OEIt2;OEIt++)
            {
                typedef  property_map<MyGraphType, transition_t>::type TransitionMap;
                TransitionMap transitionMap = get(transition_t(), (*tmp));
                Transition * transition = boost::get(transitionMap, *OEIt);
                if(transition!=line && transition->getCondition()==cond)
                {
                    res->getError(QString("There already exists a transition\nwith this condition from this state"));
                    return false;
                }
            }

            //boost::add_edge( (*(findVertex(tmp, line->startItem()))), (*(findVertex(tmp, line->endItem()))), line, (*tmp) );
            return true;
        }
        return false;
    }
}

bool Model::checkTransCondAvailabe(BaseState * source,QString cond)
{
        MyGraphType * tmp = (*subtasks)[getSubtaskName(source->getName())];

            boost::graph_traits<MyGraphType>::out_edge_iterator OEIt, OEIt2;
            tie(OEIt, OEIt2)=out_edges((*(findVertex(tmp, source))), *tmp);
            for(;OEIt!=OEIt2;OEIt++)
            {
                typedef  property_map<MyGraphType, transition_t>::type TransitionMap;
                TransitionMap transitionMap = get(transition_t(), (*tmp));
                Transition * transition = boost::get(transitionMap, *OEIt);
                if(transition->getCondition()==cond)
                {
                    res->getError(QString("There already exists a transition\nwith this condition from this state"));
                    return false;
                }
            }
        return true;
}

bool Model::tryInsertTransition(Transition * line)
{
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if (((findVertex(tmp, line->startItem()) )!=vertices(*tmp).second) && ((findVertex(tmp, line->endItem()) )!=vertices(*tmp).second ))
        {
            boost::graph_traits<MyGraphType>::out_edge_iterator OEIt, OEIt2;
            tie(OEIt, OEIt2)=out_edges((*(findVertex(tmp, line->startItem()))), *tmp);
            for(;OEIt!=OEIt2;OEIt++)
            {
                typedef  property_map<MyGraphType, transition_t>::type TransitionMap;
                TransitionMap transitionMap = get(transition_t(), (*tmp));
                Transition * transition = boost::get(transitionMap, *OEIt);
                if(transition->getCondition()==line->getCondition())
                {

                    res->getError(QString("There already exists a transition\nwith this condition from this state"));
                    return false;
                }
            }

            boost::add_edge( (*(findVertex(tmp, line->startItem()))), (*(findVertex(tmp, line->endItem()))), line, (*tmp) );
            return true;
        }
    }
    res->getError(QString("Cannot create a transition between\nstates in different tasks"));
    return false;
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


QStringList Model::checkIfOK()
{
    QStringList errors;
    char tab[200];
    //sprawdzic czy jest _init_ i _stop_ w głównym
    //sprawdzić czy jest _end_ w subtaskach
    //sprawdzić dla tranzycji czy subtask gdzieś istnieje
    //kazy stan poza end i stop musi miec przynajmniej jeden stan wyjsciowy
    //dla kazdego stanu tranzycje sa rozne, ostatnia ma warunek true

    //TODO:

    //czy z kazdego stanu da sie dojsc do end/stop(?)
    //sprawdzic czy nie są używane stany/roboty niezainicjalizowane
    //sprawdzanie czy nie są używane niezainicjalizowane sensory
    //sprawdzić czy wszystko zainicjalizowane jest używane

    //2 tablice bool jako initialized i used, sprawdzane w kazdym stanie czy initialized, sprawdzanie pod koniec czy used
    MyGraphType * tmp = (*subtasks)[mainName];
    if(tmp==NULL)std::cout<<"ZLE"<<std::endl;

    if( checkNameAvailable(QString("init"), tmp))
    {
        errors.push_back(QString( "No INIT state in main task!"));
    }
    if(  checkNameAvailable(QString("_stop_"), tmp))
    {
        errors.push_back(QString( "No STOP state in main task!"));
    }
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        if((*it).first==mainName) continue;
        MyGraphType * tmp2 = (*it).second;
        if ( checkNameAvailable(QString("_end_"), tmp2) )
        {
                std::string tmpSubName = (*it).first;
                sprintf(tab, "No END state in subtask: %s", tmpSubName.c_str());
                errors.push_back(QString( tab));
        }
    }

    typedef  property_map<MyGraphType, transition_t>::type TransitionMap;
    boost::graph_traits<MyGraphType>::edge_iterator startIt, endIt;
    typedef  property_map<MyGraphType, state_t>::type StateMap;
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
                if((*it2).first==mainName) continue;
                if (!checkNameAvailable(QString().fromStdString( transition->getSubtask()), (*it2).second))
                {
                     exists = true;
                     break;
                }
            }
            if(!exists)
            {
                StateMap stateMap = get(state_t(), (*((*it).second)));
                boost::graph_traits<MyGraphType>::vertex_descriptor u,v;
                u = source((*startIt), (*((*it).second)));
                v = target((*startIt), (*((*it).second)));
                BaseState * srcState;
                BaseState * destState;
                //srcState = (BaseState *)u;
                //destState = (BaseState *)v;
                srcState = boost::get(stateMap, u);
                destState = boost::get(stateMap, v);

                sprintf(tab, "No state %s in any subtasks, and stated in a transition between %s, %s ", transition->getSubtask().c_str(), srcState->getName().toStdString().c_str(), destState->getName().toStdString().c_str());
                errors.push_back(QString(tab));
            }
        }
        tmp = (*it).second;

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
                if(state->getName().toLower()!=QString( "_end_") && state->getName().toLower()!=QString( "_stop_"))
                {
                    QString tmpQstring = state->getName().append(QString(  " state has no outgoing edges and should have at least 1"));
                    errors.push_back(tmpQstring);
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
                    QString tmpQstring = state->getName().append(QString( " state should have last\nTransition with condition true"));
                    errors.push_back(tmpQstring);
                }
            }
        }
    }
    return errors;
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

bool Model::ReplaceState(BaseState * oldState, BaseState * newState,  QString oldStateName)
{
    //check if the state wasn't deleted
    std::string subtaskName = getSubtaskName(oldStateName);
    if(subtaskName==std::string(""))
    {
        res->getError(QString("The state you were editing has been deleted,\nplease choose the insert option to insert the state"));
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
        res->getError(QString("The state you were editing has been deleted,\nplease choose the insert option to insert the state"));
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
        res->getError(QString("The state you were editing has been deleted,\nplease choose the insert option to insert the state"));
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
        res->getError(QString("The state you were editing has been deleted,\nplease choose the insert option to insert the state"));
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
    QString tmpSaveName = QString(SaveFolder).append(QString().fromStdString(FileName));
    QFile* file = new QFile(tmpSaveName);
    std::cout<<"SAVE: "<<tmpSaveName.toStdString()<<std::endl;
    file->open( QIODevice::WriteOnly);
    QXmlStreamWriter * writer = new QXmlStreamWriter(file);
    writer->setAutoFormatting(1);
    writer->setCodec("UTF-8");
    writer->writeStartDocument("1.0");
    writer->writeDTD(QString("<!DOCTYPE TaskDescription SYSTEM \"fsautomat.dtd\" >"));

    typedef  property_map<MyGraphType, state_t>::type StateMap;
    StateMap stateMap = get(state_t(), *G);

    typedef  property_map<MyGraphType, transition_t>::type TransitionMap;
    TransitionMap transitionMap = get(transition_t(), *G);

    BaseState *State;
    Transition * transition;





    writer->writeStartElement("TaskDescription");
    if(ifMain)
    {
        res->SaveGraphicsAttributes(writer);
    }
    for (;first != last;first++)
    {
      State = boost::get(stateMap, *first);
      writer->writeStartElement("State");
      writer->writeAttribute(QString("id"), State->getName());
      writer->writeAttribute(QString("type"), QString().fromStdString(STATE_TYPE_TABLE[State->getType()]));
      char tab[20];
      sprintf(tab, "%lf", State->pos().x());
      writer->writeTextElement("PosX", QString(tab));
      sprintf(tab, "%lf", State->pos().y());
      writer->writeTextElement("PosY", QString(tab));


      State->Print(writer);


      boost::graph_traits<MyGraphType>::out_edge_iterator startIt, endIt;
      tie(startIt, endIt)=out_edges((*first), *G);
      for ( ;startIt!=endIt;startIt++)
      {
          transition = boost::get(transitionMap, *startIt);
          transition->Print(writer);
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
            writer->writeAttribute("href", QString(SaveFolder).append(QString().fromStdString(subtaskFileName)));
            writer->writeAttribute("parse", "xml");
            writer->writeAttribute("xmlns:xi", "http://www.w3.org/2001/XInclude");
            writer->writeEndElement();
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

void Model::setMainName(QString myFile)
{
    if(myFile.toStdString()==mainName && (*subtasks)[mainName]==NULL)
    {
        (*subtasks)[mainName]=new MyGraphType();
        return;
    }
    if(myFile.toStdString()==mainName)return;
    MyGraphType * tmp = (*subtasks)[mainName];
    if(tmp!=NULL)
    {
        subtasks->insert(std::make_pair(myFile.toStdString(), tmp));
    }
    else
    {
        subtasks->insert(std::make_pair(myFile.toStdString(), new MyGraphType()));
    }
    subtasks->erase(mainName);
    mainName = myFile.toStdString();

}

BaseState * Model::getState(QString name, std::string subtaskName)
{
    std::cout<<"IN GET STATE"<<std::endl;
    if (!checkSubtaskExists(subtaskName))
    {
        return NULL;
    }
    std::cout<<"Graph existst"<<std::endl;
    MyGraphType * graph = (*subtasks)[subtaskName];
    property_map<MyGraphType, state_t>::type State = get(state_t(), (*graph));
    graph_traits<MyGraphType>::vertex_iterator first, last;
    tie(first, last) = vertices(*graph);
    for ( ;first!=last; first++)
    {
        BaseState * tmp = boost::get(State, (*first));
        if (tmp->getName()  == name) return tmp;
    }
    return NULL;
}

bool Model::checkSubtaskExists(std::string Name)
{
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        if((*it).first==Name)
        {
            return true;
        }
    }
    return false;
}

void Model::deleteAll()
{
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;

        property_map<MyGraphType, transition_t>::type TransitionMap  = get(transition_t(), (*tmp));
        boost::graph_traits<MyGraphType>::edge_iterator startIt, endIt;
        tie(startIt, endIt)=edges(*tmp);
        for(;startIt!=endIt;)
        {
            Transition * transition = boost::get(TransitionMap, *startIt);
            res->deleteTrans(transition);
            tie(startIt, endIt)=edges(*tmp);
           // boost::remove_edge(startIt, *tmp);
            //delete transition;
        }

        property_map<MyGraphType, state_t>::type StateMap = get(state_t(), (*tmp));
        boost::graph_traits<MyGraphType>::vertex_iterator first,last;
        tie(first, last) = vertices(*tmp);
        for (;first!=last;)
        {
            BaseState * state = boost::get(StateMap, (*first));
            res->deleteState(state);
            tie(first, last) = vertices(*tmp);
           // boost::remove_vertex(first, *tmp);
            //delete state;
        }

        delete tmp;
        subtasks->erase(it);
    }
    addSubtask(QString().fromStdString(mainName));
}



void Model::changeSubtaskName(QString oldName, QString NewName)
{
    if(oldName.toStdString()==mainName) mainName = NewName.toStdString();
    MyGraphType  * tmp;
    for (std::map<std::string, MyGraphType *>::iterator it = subtasks->begin();it!=subtasks->end();it++)
    {
        if((*it).first == oldName.toStdString())
        {
            tmp = (*it).second;
            subtasks->erase(it);
            break;
        }
    }
    (*subtasks)[NewName.toStdString()]= tmp;

}

void Model::DeleteSubtask(QString Name)
{

    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        if((*it).first != Name.toStdString()) continue;
        MyGraphType * tmp = (*it).second;

        property_map<MyGraphType, transition_t>::type TransitionMap  = get(transition_t(), (*tmp));
        boost::graph_traits<MyGraphType>::edge_iterator startIt, endIt;
        tie(startIt, endIt)=edges(*tmp);
        for(;startIt!=endIt;)
        {
            Transition * transition = boost::get(TransitionMap, *startIt);
            res->deleteTrans(transition);
            tie(startIt, endIt)=edges(*tmp);
           // boost::remove_edge(startIt, *tmp);
            //delete transition;
        }

        property_map<MyGraphType, state_t>::type StateMap = get(state_t(), (*tmp));
        boost::graph_traits<MyGraphType>::vertex_iterator first,last;
        tie(first, last) = vertices(*tmp);
        for (;first!=last;)
        {
            BaseState * state = boost::get(StateMap, (*first));
            res->deleteState(state);
            tie(first, last) = vertices(*tmp);
           // boost::remove_vertex(first, *tmp);
            //delete state;
        }

        if(Name.toStdString()!=mainName)
        {
            delete tmp;
            subtasks->erase(it);
        }
        break;
    }
}





