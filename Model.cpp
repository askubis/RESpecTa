#include "Model.h"
#include "GraphFunctions.cpp"

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
            printStates(vertices((*tmp)).first, vertices((*tmp)).second, (*tmp), std::string(filename.c_str()), subtasks, mainName);
        }
        else
        {
            printStates(vertices((*tmp)).first, vertices((*tmp)).second, (*tmp), std::string((*it).first+".xml"), NULL, "");
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

void Model::addState(BaseState * item, std::string subtaskName)
{
    MyGraphType::vertex_descriptor v_new;
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        if((*it).first == subtaskName)
        {
            v_new = boost::add_vertex(item, (*(*subtasks)[subtaskName]));
        }
    }
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
        if (!checkStateNameAvailable(vertices(*tmp).first,vertices(*tmp).second, (*tmp), name))
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
    return getStateNames(vertices(*tmp).first, vertices(*tmp).second, (*tmp));
}


void Model::checkIfOK()
{
    char tab[200];
    //sprawdzic czy jest _init_ i _stop_ w głównym
    //sprawdzić czy jest _end_ w subtaskach
    //sprawdzić dla tranzycji czy subtask gdzieś istnieje
    //kazy stan poza end i stop musi miec przynajmniej jeden stan wyjsciowy
    MyGraphType * tmp = (*subtasks)[mainName];
    if(checkNameAvailable(QString("_INIT_"), tmp) &&  checkNameAvailable(QString("_init_"), tmp))
    {
        res->getError(QString().fromStdString("No INIT state in main task!"));
    }
    if(checkNameAvailable(QString("_STOP_"), tmp) &&  checkNameAvailable(QString("_stop_"), tmp))
    {
        res->getError(QString().fromStdString("No STOP state in main task!"));
    }
    for(std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end();it++)
    {
        if((*it).first==mainName) continue;
        MyGraphType * tmp2 = (*it).second;
        if ( checkNameAvailable(QString("_END_"), tmp2) && checkNameAvailable(QString("_end_"), tmp2) )
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
        typedef  property_map<MyGraphType, state_t>::type StateMap;
        StateMap stateMap = get(state_t(), (*((*it).second)));
        boost::graph_traits<MyGraphType>::vertex_iterator first, last;
        tie(first, last) = vertices(*tmp);
        for(;first!=last;first++)
        {
            BaseState * state = boost::get(stateMap, *first);
            boost::graph_traits<MyGraphType>::out_edge_iterator OEIt, OEIt2;
            tie(OEIt, OEIt2)=out_edges((*first), *tmp);
            if(OEIt==OEIt2)//no outgoing edges
            {
                std::string namestring = state->getName().toStdString();
                if(namestring!="_END_" && namestring!="_STOP_")
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
    if (!checkStateNameAvailable(vertices(*G).first,vertices(*G).second, (*G), name))
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
        if (!checkStateNameAvailable(vertices(*tmp).first,vertices(*tmp).second, (*tmp), StateName))
        {
           return (*it).first;
        }
    }
    return std::string("");
}





