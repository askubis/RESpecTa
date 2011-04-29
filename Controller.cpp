#include "Controller.h"

void Controller::saveClicked()
{
    mod->save("MAIN.xml");
}

void Controller::deleteTransition(Transition * transition)
{
    mod->deleteTransition(transition);
}

void Controller::deleteState(BaseState * state)
{
    mod->deleteState(state);
}

void Controller::addState(BaseState * item, std::string subtaskName)
{
    mod->addState(item, subtaskName);
}

bool Controller::tryInsertTransition(Transition * trans)
{
    return mod->tryInsertTransition(trans);
}

void Controller::addSubtask(QString name)
{
    mod->addSubtask(name);
}


