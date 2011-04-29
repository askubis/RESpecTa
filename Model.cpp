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

    for (std::map<std::string, MyGraphType *>::iterator it = subtasks->begin();it!=subtasks->end();it++)
    {
        MyGraphType * tmp = (*it).second;
        if(((*it).first)==mainName)
        {
            printStates(vertices((*tmp)).first, vertices((*tmp)).second, (*tmp), std::string(filename.c_str()), subtasks);
        }
        else
        {
            printStates(vertices((*tmp)).first, vertices((*tmp)).second, (*tmp), std::string((*it).first+".xml"), NULL);
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
    (*(this->subtasks))[name.toStdString()] = new MyGraphType();
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





