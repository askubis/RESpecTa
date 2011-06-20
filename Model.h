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
    void deleteAll();
    void DeleteTask(QString Name);
    int vertNum(QString Name);

    QString getSubNameOfTrans(Transition * trans);

    void DeleteSubtask(QString Name);
    void changeSubtaskName(QString oldName, QString NewName);

    bool checkTransCondAvailabe(BaseState * source,QString cond);
    bool checkSubtaskExists(QString Name);
    BaseState * getState(QString name, QString subtaskName);
    void setMainName(QString newName);
    void save(QString filename);
    void deleteTransition(Transition * transition);
    void deleteState(BaseState * state);
    bool addState(BaseState * item, QString subtaskName);
    bool tryInsertTransition(Transition * trans);
    bool checkNameAvailable(QString name);
    void addSubtask(QString name);
    QStringList getTasksNameLists();
    QStringList getTasksNameListsWithoutMain();
    QStringList getAllStateNames(QString sub);
    //bool checkStateNameIsAvailable( MyGraphType &G, QString given);
    QStringList checkIfOK();
    bool checkNameAvailable(QString name, MyGraphType * G);
    QString getSubtaskName(QString StateName);
    bool ReplaceState(BaseState * oldState, BaseState * newState,  QString oldStateName);

    void MoveTransitionUp(BaseState * st, int index);
    void MoveTransitionDown(BaseState * st, int index);

    std::vector<Transition *> getTransitions(BaseState * state);

    bool checkTransitonExists(Transition * trans);

    boost::graph_traits<MyGraphType>::edge_iterator findEdge ( MyGraphType * graph, Transition * toFind);
    boost::graph_traits<MyGraphType>::vertex_iterator findVertex ( MyGraphType * graph, BaseState * toFind);
    void printStates(MyGraphType *G, std::string FileName, bool ifMain);
    bool checkStateNameAvailable(MyGraphType *G, QString given);
    QStringList getStateNames(MyGraphType G);


    void setView(RESpecTa * newres){res=newres;}
    QString getMainName(){return mainName;}

    bool checkTransCondAvailabe(Transition * tr,QString cond);

    void setSaveFolder(QString newSaveFolder){SaveFolder=newSaveFolder;}


signals:
    void reportError(QString);

private:
    RESpecTa * res;
    QString mainName;
    std::map<QString, MyGraphType *> * subtasks;
    QString SaveFolder;

};

#endif // MODEL_H
