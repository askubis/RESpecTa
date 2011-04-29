#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Model.h"
class RESpecTa;

class Controller
{
public:
    Controller(){}
    Controller(Model * newmod){mod=newmod;}
    void setView(RESpecTa * newres){res=newres;}
    void saveClicked();
    void deleteTransition(Transition * transition);
    void deleteState(BaseState * state);
    void addState(BaseState * item, std::string subtaskName);
    bool tryInsertTransition(Transition * trans);
    void addSubtask(QString name);

private:

    Model * mod;
    RESpecTa * res;

};

#endif // CONTROLLER_H
