#include "Model.h"
//#include "GraphFunctions.cpp"



Model::Model()
{
    subtasks = new std::map<QString, MyGraphType *>();
    mainName = "MAIN";
    subtasks->insert(std::make_pair(mainName, new MyGraphType()));
    changed=false;
    changeBlocked=false;
}

void Model::save(QString myFile)
{
    std::string filename = myFile.toStdString();
myFile.chop(4);
QString logPath =SaveFolder+ myFile;
logPath.append(".log");
int ind = myFile.lastIndexOf('/');
myFile.remove(0,ind+1);

    for(std::map<QString, MyGraphType *>::iterator it = subtasks->begin();it!=subtasks->end();it++)
    {
        if((*it).first==mainName)continue;

        if(myFile==(*it).first)
        {
            res->getError(QString("a subtask exists with a name you wanted to\nsave your graph with, choose other filename"));
            res->clearSaveName();
            return;
        }
    }


   if(myFile!=mainName)
   {
     subtasks->insert(std::make_pair(myFile, (*subtasks)[mainName]));
     subtasks->erase(mainName);
     mainName = myFile;
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

    for (std::map<QString, MyGraphType *>::iterator it = subtasks->begin();it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if(((*it).first)==mainName)
        {
            if(!myFile.endsWith(".xml"))
            {
                myFile.append(QString(".xml"));
            }
            printStates(tmp, myFile.toStdString(),true);
        }
        else
        {
            printStates(tmp, (*it).first.toStdString()+".xml", false);
        }
    }
    setChanged(false);
    return;
}

void Model::deleteTransition(Transition * transition)
{
    for(std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if((findEdge(tmp, transition) )!=edges(*tmp).second)
            boost::remove_edge((*(findEdge(tmp, transition))), (*tmp));
    }
    transition->startItem()->removeTransition(transition);
    transition->endItem()->removeTransition(transition);
    setChanged(true);
}

void Model::deleteState(BaseState * state)
{
    for(std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if((findVertex(tmp, state) )!=vertices(*tmp).second)
            boost::remove_vertex((*(findVertex(tmp, state))), (*tmp));
    }
    setChanged(true);
}

bool Model::addState(BaseState * item, QString subtaskName)
{
    if(item ==NULL)
    {
        res->getError(QString("A problem has been detected, code:\ntrying to insert NULL value").append(item->getName()));
    }
    if(!checkNameAvailable(item->getName(),(*subtasks)[subtaskName]))
    {
        res->getError(QString( "This state already exists in the given subtask").append(item->getName()));
        return false;
    }

    boost::add_vertex(item, (*(*subtasks)[subtaskName]));
    setChanged(true);
    return true;

}

bool Model::checkTransCondAvailabe(Transition * line,QString cond)
{
    for(std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
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
    }
    return false;
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
    for(std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
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
            setChanged(true);
            return true;
        }
    }
    res->getError(QString("Cannot create a transition between\nstates in different tasks"));
    return false;
}

bool Model::checkNameAvailable(QString name)
{
    for(std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if (!checkNameAvailable(name,tmp))
        {
           return false;
        }
    }
    return true;
}

void Model::addSubtask(QString name)
{
    subtasks->insert(std::make_pair(name, new MyGraphType()));
    changed=1;
}

QStringList Model::getTasksNameLists()
{
    QStringList subtaskList;
    for (std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end() ;it++)
    {
        subtaskList<<(*it).first;
    }
    return subtaskList;
}

QStringList Model::getTasksNameListsWithoutMain()
{
    QStringList subtaskList;
    for (std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end() ;it++)
    {
        if((*it).first!=mainName)subtaskList<<(*it).first;
    }
    return subtaskList;
}

QStringList Model::getAllStateNames(QString sub)
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

    //sprawdzic czy nie są używane stany/roboty niezainicjalizowane
    //sprawdzanie czy nie są używane niezainicjalizowane sensory
    //sprawdzić czy wszystko zainicjalizowane jest używane

    //TODO:

    //czy z kazdego stanu da sie dojsc do end/stop(?)
    bool SensorUsed[SENSORS_NUMBER], SensorInitialized[SENSORS_NUMBER];
    for(int i=0;i<SENSORS_NUMBER;i++)
    {
        Sensor sen = (Sensor)i;
        SensorUsed[sen]=false;
        SensorInitialized[sen]=false;
    }
    //bool RobotUsed[ROBOTS_NUMBER], RobotInitialized[ROBOTS_NUMBER];
    bool genUsed[ROBOTS_NUMBER][GENERATORS_NUMBER], genInitialized[ROBOTS_NUMBER][GENERATORS_NUMBER];//wystarcza za roboty
    for(int i=0;i<ROBOTS_NUMBER;i++)
    {
        Robot rob = (Robot)i;
        for(int j=0;j<GENERATORS_NUMBER;j++)
        {
            GeneratorType genType = (GeneratorType)j;
            genUsed[rob][genType]=false;
            genInitialized[rob][genType]=false;
        }
    }
    sysInitState * tmpState = (sysInitState *)getState("INIT", mainName);
    foreach(genInit init, tmpState->getInits())
    {
        //RobotInitialized[init.robot]=true;
        for(std::vector < std::pair<GeneratorType, int> >::iterator it = init.init_values.begin();it!=init.init_values.end();it++)
        {
            genInitialized[init.robot][(*it).first]=true;
        }
    }
    foreach(Sensor sen, tmpState->getSensors())
    {
        SensorInitialized[sen]=true;
    }
    for(std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * gr = (*it).second;
        typedef  property_map<MyGraphType, state_t>::type st_map;
        st_map stateMap = get(state_t(), (*gr));
        boost::graph_traits<MyGraphType>::vertex_iterator first, last;
        tie(first, last) = vertices(*gr);
        for(;first!=last;first++)
        {
            BaseState * state = boost::get(stateMap, *first);
            //check
            GetSensorState * tmpSensState;
            RunGenState * tmpRunState;
            switch(state->getType())
            {
                case GET_SENSOR_READING:
                tmpSensState = (GetSensorState *)state;
                SensorUsed[tmpSensState->getSensor()]=true;
                break;
                case RUN_GENERATOR:
                tmpRunState = (RunGenState *)state;
                genUsed[tmpRunState->getRobot()][tmpRunState->getGenType()]=true;
                break;
                default:
                break;
            }
        }
    }
    for(int i=0;i<SENSORS_NUMBER;i++)
    {
        Sensor sen = (Sensor)i;
        if(SensorUsed[i]^SensorInitialized[i])
        {
            errors+=QString("Sensor initizalized but not used, or used but not initizalized ").append(QString().fromStdString(SENSOR_TABLE[sen]));
        }
    }
    for(int i=0;i<ROBOTS_NUMBER;i++)
    {
        Robot rob = (Robot)i;
        for(int j=0;j<GENERATORS_NUMBER;j++)
        {
            GeneratorType genType = (GeneratorType)j;
            if(genUsed[rob][genType]^genInitialized[rob][genType])
            {
                errors+=QString("Generator initizalized but not used, or used but not initizalized ").append(QString().fromStdString(GENERATOR_TYPE_TABLE[genType])).append(QString(" for Robot: ")).append(QString().fromStdString(ROBOT_TABLE[rob]));
            }
        }

    }





    MyGraphType * tmp = (*subtasks)[mainName];

    if( checkNameAvailable(QString("init"), tmp))
    {
        errors.push_back(QString( "No INIT state in main task!"));
    }
    if(  checkNameAvailable(QString("_stop_"), tmp))
    {
        errors.push_back(QString( "No STOP state in main task!"));
    }
    for(std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        if((*it).first==mainName) continue;
        MyGraphType * tmp2 = (*it).second;
        if ( checkNameAvailable(QString("_end_"), tmp2) )
        {
                QString tmpSubName = (*it).first;
                sprintf(tab, "No END state in subtask: %s", tmpSubName.toStdString().c_str());
                errors.push_back(QString( tab));
        }
    }

    typedef  property_map<MyGraphType, transition_t>::type TransitionMap;
    boost::graph_traits<MyGraphType>::edge_iterator startIt, endIt;
    typedef  property_map<MyGraphType, state_t>::type StateMap;
    for(std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
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
            for(std::map<QString, MyGraphType *>::iterator it2 = subtasks->begin(); it2!=subtasks->end();it2++)
            {
                if((*it2).first==mainName) continue;
                if (!checkNameAvailable(transition->getSubtask(), (*it2).second))
                {
                     exists = true;
                     break;
                }
            }
            if(!exists)
            {
                StateMap stateMap = get(state_t(), (*((*it).second)));
                VertexType u,v;
                u = source((*startIt), (*((*it).second)));
                v = target((*startIt), (*((*it).second)));
                BaseState * srcState;
                BaseState * destState;
                //srcState = (BaseState *)u;
                //destState = (BaseState *)v;
                srcState = boost::get(stateMap, u);
                destState = boost::get(stateMap, v);

                sprintf(tab, "No state %s in any subtasks, and stated in a transition between %s, %s ", transition->getSubtask().toStdString().c_str(), srcState->getName().toStdString().c_str(), destState->getName().toStdString().c_str());
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


bool Model::checkNameAvailable(QString given, MyGraphType * G)
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


QString Model::getSubtaskName(QString StateName)
{
    for(std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if (!checkNameAvailable(StateName,tmp))
        {
           return (*it).first;
        }
    }
    return QString("");
}

bool Model::ReplaceState(BaseState * oldState, BaseState * newState,  QString oldStateName)
{
    //check if the state wasn't deleted
    QString subtaskName = getSubtaskName(oldStateName);
    if(subtaskName==QString(""))
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
        setChanged(true);
        return true;
    }
    return false;


}


void Model::MoveTransitionUp(BaseState * st, int index)
{
    QString subtaskName = getSubtaskName(st->getName());
    if(subtaskName==QString(""))
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
    setChanged(true);

}

void Model::MoveTransitionDown(BaseState * st, int index)
{
    QString subtaskName = getSubtaskName(st->getName());
    if(subtaskName==QString(""))
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
    setChanged(true);
}

std::vector<Transition *> Model::getTransitions(BaseState * st)
{
    std::vector<Transition *> tranVect;
    QString subtaskName = getSubtaskName(st->getName());
    if(subtaskName==QString(""))
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
    for (std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end() ;it++)
    {
        MyGraphType * tmpGraph = (*it).second;
        if(findEdge(tmpGraph,trans)!= edges(*tmpGraph).second) return true;
    }
    return false;
}

QString Model::getSubNameOfTrans(Transition * trans)
{
    for (std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end() ;it++)
    {
        MyGraphType * tmpGraph = (*it).second;
        if(findEdge(tmpGraph,trans)!= edges(*tmpGraph).second) return (*it).first;
    }
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
    QString SubName = QString().fromStdString(FileName);
    SubName.chop(4);

    boost::graph_traits<MyGraphType>::vertex_iterator first,last;
    tie(first, last) = vertices(*G);
    QString tmpSaveName = QString(SaveFolder).append(QString().fromStdString(FileName));
    QFile* file = new QFile(tmpSaveName);
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
    res->SaveGraphicsAttributes(writer, SubName);

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
        for (std::map<QString, MyGraphType *>::iterator it = subtasks->begin();it!=subtasks->end();it++)
        {
            if((*it).first == mainName)continue;
            std::string subtaskFileName = (*it).first.toStdString() + ".xml";
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

void Model::setMainName(QString myFile)
{
    if(myFile==mainName && (*subtasks)[mainName]==NULL)
    {
        (*subtasks)[mainName]=new MyGraphType();
        return;
    }
    if(myFile==mainName)return;
    MyGraphType * tmp = (*subtasks)[mainName];
    if(tmp!=NULL)
    {
        subtasks->insert(std::make_pair(myFile, tmp));
    }
    else
    {
        subtasks->insert(std::make_pair(myFile, new MyGraphType()));
    }
    subtasks->erase(mainName);
    mainName = myFile;
    setChanged(true);

}

BaseState * Model::getState(QString name, QString subtaskName)
{
    if (!checkSubtaskExists(subtaskName))
    {
        return NULL;
    }
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

bool Model::checkSubtaskExists(QString Name)
{
    return subtasks->find(Name)!=subtasks->end();
}

void Model::DeleteTask(QString Name)
{
    if(subtasks->find(Name)==subtasks->end())return;
    MyGraphType * tmp = (*subtasks)[Name];
    if(tmp!=NULL)
    {
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

        if(Name!=mainName)
        {
            delete tmp;
            subtasks->erase(subtasks->find(Name));
        }
    }
    setChanged(true);
}

void Model::deleteAll()
{
    for(std::map<QString, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
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
    addSubtask(mainName);
    setChanged(true);
}



void Model::changeSubtaskName(QString oldName, QString NewName)
{
    if(oldName==mainName) mainName = NewName;
    MyGraphType  * tmp;
    for (std::map<QString, MyGraphType *>::iterator it = subtasks->begin();it!=subtasks->end();it++)
    {
        if((*it).first == oldName)
        {
            tmp = (*it).second;
            subtasks->erase(it);
            break;
        }
    }
    (*subtasks)[NewName]= tmp;
    setChanged(true);

}


int Model::vertNum(QString Name)
{
    if(subtasks->find(Name)==subtasks->end())return 0;
    return boost::num_vertices(*((*subtasks)[Name]));
}

MyGraphType * Model::getGraph(QString Name)
{
    if(subtasks->find(Name)!=subtasks->end())
        return (*subtasks)[Name];
    return NULL;
}

BaseState * Model::getState(MyGraphType * tmp, int index)
{
    if(index>boost::num_vertices(*tmp))return NULL;
    boost::graph_traits<MyGraphType>::vertex_iterator first, last;
    tie(first, last) = vertices(*tmp);
    for(int i=0;i<index;i++, first++)
    {}
    typedef  property_map<MyGraphType, state_t>::type StateMap;
    StateMap stateMap = get(state_t(), (*tmp));

    BaseState * state = boost::get(stateMap, *first);
    return state;
}

void Model::setChanged(bool newChanged)
{
    changed=newChanged;
    if(!changeBlocked && changed)res->WasChanged();
}




