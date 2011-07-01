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


        //*************     COUNT   ***********//
    int vertNum(QString Name);

        //*************     DELETE  ***********//
    void deleteAll();
    void deleteTransition(Transition * transition);
    void deleteState(BaseState * state);
    void DeleteTask(QString Name);

        //*************     ADD     ***********//
    void addSubtask(QString name);
    bool addState(BaseState * item, QString subtaskName);
    bool tryInsertTransition(Transition * trans);

        //*************     CHANGE  ***********//
    void changeSubtaskName(QString oldName, QString NewName);
    bool ReplaceState(BaseState * oldState, BaseState * newState,  QString oldStateName);
    void MoveTransitionUp(BaseState * st, int index);
    void MoveTransitionDown(BaseState * st, int index);

        //*************     GET     ***********//
    BaseState * getState(QString name, QString subtaskName);
    BaseState * getState(MyGraphType * graph, int i);
    std::vector<Transition *> getTransitions(BaseState * state);
    MyGraphType * getGraph(QString Name);
    QString getSubtaskName(QString StateName);
    QString getMainName(){return mainName;}
    QString getSubNameOfTrans(Transition * trans);
    QStringList getStateNames(MyGraphType G);
    QStringList getTasksNameLists();
    QStringList getTasksNameListsWithoutMain();
    QStringList getAllStateNames(QString sub);

    boost::graph_traits<MyGraphType>::edge_iterator findEdge ( MyGraphType * graph, Transition * toFind);
    boost::graph_traits<MyGraphType>::vertex_iterator findVertex ( MyGraphType * graph, BaseState * toFind);

        //*************     SET     ***********//
    void setMainName(QString newName);
    void setView(RESpecTa * newres){res=newres;}
    void setSaveFolder(QString newSaveFolder){SaveFolder=newSaveFolder;}

        //*************     CHECK   ***********//
    bool checkTransCondAvailabe(BaseState * source,QString cond);
    bool checkSubtaskExists(QString Name);
    bool checkNameAvailable(QString name, MyGraphType * G);
    bool checkNameAvailable(QString name);
    bool checkTransitonExists(Transition * trans);
    bool checkTransCondAvailabe(Transition * tr,QString cond);

        //*************     SAVE    ***********//
    void save(QString filename);
    void printStates(MyGraphType *G, std::string FileName, bool ifMain);
    QStringList checkIfOK();

        //*************     OTHER   ***********//
    void setChanged(bool newChanged);
    bool wasChanged(){return changed;}
    void setBlock(bool block){changeBlocked=block;}

signals:
    void reportError(QString);

private:
    RESpecTa * res;
    QString mainName;
    std::map<QString, MyGraphType *> * subtasks;
    QString SaveFolder;
    bool changed;
    bool changeBlocked;
};

#endif // MODEL_H
