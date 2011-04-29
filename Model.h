#ifndef MODEL_H
#define MODEL_H
#include "globals.h"
#include "Graph.h"


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


private:

    std::string mainName;
    std::map<std::string, MyGraphType *> * subtasks;
};

#endif // MODEL_H
