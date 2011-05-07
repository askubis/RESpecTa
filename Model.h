#ifndef MODEL_H
#define MODEL_H
class Model;

#include "globals.h"
#include "Graph.h"
#include "respecta.h"


class Model
{

public:
    Model();
    void save(std::string filename);
    void deleteTransition(Transition * transition);
    void deleteState(BaseState * state);
    void addState(BaseState * item, std::string subtaskName);
    bool tryInsertTransition(Transition * trans);
    bool checkNameAvailable(QString name);
    void addSubtask(QString name);
    QStringList getTasksNameLists();
    QStringList getTasksNameListsWithoutMain();
    QStringList getAllStateNames(std::string sub);
    //bool checkStateNameIsAvailable( MyGraphType &G, QString given);
    void checkIfOK();
    bool checkNameAvailable(QString name, MyGraphType * G);
    std::string getSubtaskName(QString StateName);


    void setView(RESpecTa * newres){res=newres;}
    std::string getMainName(){return mainName;}

    signals:
    void reportError(QString);

private:
    RESpecTa * res;
    std::string mainName;
    std::map<std::string, MyGraphType *> * subtasks;
};

#endif // MODEL_H
