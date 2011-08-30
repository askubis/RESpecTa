class Model;

#ifndef MODEL_H
#define MODEL_H

#include "globals.h"
#include "Graph.h"
#include "respecta.h"

/**
*   Class responsible for keeping the data and allowing operation on the data.
*/
class Model
{
public:
    /**
    *   Constructor creating subtask called "MAIN".
    */
    Model();

        //*************     COUNT   ***********//
    /**
    *   Returns Number of Vertices in the subtask defined by the SubtaskName.
    */
    int vertNum(QString SubtaskName);

        //*************     DELETE  ***********//

    /**
    *   Function removing all vertices and edges from a task with name=name.
    */
    void CleanTask(QString name);

    /**
    *   Clears the model leaving only empty main state.
    */
    void deleteAll();
    /**
    *   Removes the given transition from the model.
    */
    void deleteTransition(Transition * transition);
    /**
    *   Removes the given state from the model.
    */
    void deleteState(BaseState * state);
    /**
    *   Deletes all states and transitions of the task from model,
    *   if it's not the main task erases the given Subtask from the model.
    */
    void DeleteTask(QString SubtaskName);

        //*************     ADD     ***********//
    /**
    *   Adds a subtask to the model.
    *   @param name Name of subtask which will be created.
    */
    void addSubtask(QString name);
    /**
    *   Adds a state to a subtask.
    *   @param item State, which will be inserted.
    *   @param subtas
    Q_OBJECTkName Name of subtask, to which the state will be inserted.
    *   @returns True if operation successful.
    */
    bool addState(BaseState * item, QString subtaskName);
    /**
    *   Adds a subtask to the model.
    *   @param trans Transition which will be inserted.
    *   @returns True if operation successful.
    */
    bool tryInsertTransition(Transition * trans);

        //*************     CHANGE  ***********//
    /*void changeSourceStateofTrans(Transition * tr, QString newstatename);
    void changeDestStateofTrans(Transition * tr, QString newstatename);*/


    /**
    *   Changes the name of subtask from oldName to NewName.
    */
    void changeSubtaskName(QString oldName, QString NewName);
    /**
    *   Changes the oldState to newState in the model.
    *   @returns True if operation successful.
    */
    bool ReplaceState(BaseState * oldState, BaseState * newState);
    /**
    *   Moves the transition at index _index one position Up in the Transition List in the graph representing task.
    */
    void MoveTransitionUp(BaseState * st, int _index);
    /**
    *   Moves the transition at index _index one position Down in the Transition List in the graph representing task.
    */
    void MoveTransitionDown(BaseState * st, int _index);

        //*************     GET     ***********//


    /**
    *   Function returning the i'th transition going out of state st.
    */
    Transition * getTransition(BaseState *st, int i);

    /**
    *   Returns names of all States in the task sub without the end state.
    */
    QStringList getAllStartStateNames(QString sub)
    {
        QStringList list = getAllStateNames(sub);
        list.removeOne("_END_");
        list.removeOne("_STOP_");
        return list;
    }

    /**
    *   Returns all names of states in task sub without init state.
    */
    QStringList getAllEndStateNames(QString sub)
    {
        QStringList list = getStateNames((*((*subtasks)[sub])));
        list.removeOne("INIT");
        return list;
    }

    /**
    *   Returns the State with given name. Not for use for _END_ or _STOP_ states.
    */
    BaseState * getState(QString name);
    /**
    *   Returns the State with given name from the subtask with given subtaskName.
    */
    BaseState * getState(QString name, QString subtaskName);
    /**
    *   Returns the State at index i in Graph graph.
    */
    BaseState * getState(MyGraphType * graph, int i);
    /**
    *   Returns all transitions of a state from the model.
    */
    std::vector<Transition *> getTransitions(BaseState * state);
    /**
    *   Returns Graph with given Name.
    */
    MyGraphType * getGraph(QString Name);
    /**
    *   Returns Name of subtask containing a state with given StateName.
    */
    QString getSubtaskName(QString StateName);
    /**
    *   Returns Name of subtask containing a state State.
    */
    QString getSubtaskName(BaseState * State );
    /**
    *   Returns Name of the main task.
    */
    QString getMainName(){return mainName;}
    /**
    *   Returns Name of subtask containing given transition.
    */
    QString getSubNameOfTrans(Transition * transition);
    /**
    *   Returns List with names of all states from the graph G.
    */
    QStringList getStateNames(MyGraphType G);
    /**
    *   Returns List with names of all tasks from the model.
    */
    QStringList getTasksNameLists();
    /**
    *   Returns List with names of all tasks from the model without the main task..
    */
    QStringList getTasksNameListsWithoutMain();
    /**
    *   Returns List with names of all states from the subtask with name sub.
    */
    QStringList getAllStateNames(QString sub);

    /**
    *   Returns edge_iterator of the Edge containing transition toFind in the graph.
    */
    boost::graph_traits<MyGraphType>::edge_iterator findEdge ( MyGraphType * graph, Transition * toFind);
    /**
    *   Returns vertex_iterator of the Vertex containing state toFind in the graph.
    */
    boost::graph_traits<MyGraphType>::vertex_iterator findVertex ( MyGraphType * graph, BaseState * toFind);

        //*************     SET     ***********//
    /**
    *   Changes name of the main task to newName.
    */
    void setMainName(QString newName);
    /**
    *   Sets main window to newres.
    */
    void setView(RESpecTa * newres){res=newres;}
    /**
    *   Sets save folder to newSaveFolder.
    */
    void setSaveFolder(QString newSaveFolder){SaveFolder=newSaveFolder;}

        //*************     CHECK   ***********//
    /**
    *   Checks if condition cond is available for the state source.
    *   @returns True if the condition cond hasn't been used as a out-condition from the state source.
    */
    bool checkTransCondAvailabe(BaseState * source,ConditionType condType, QString cond);
    /**
    *   Checks if subtask with name Name exists.
    *   @returns True if subtask with name Name exists.
    */
    bool checkSubtaskExists(QString Name);
    /**
    *   Checks if name Name is available for graph G.
    *   @returns True if no state with name Name exists in graph G.
    */
    bool checkNameAvailable(QString Name, MyGraphType * G);
    /**
    *   Checks if state with name Name is present in the model.
    *   @returns True if subtask containing state with name Name exists.
    */
    bool checkNameAvailable(QString Name);
    /**
    *   Checks if Trnsition trans is present in the model.
    *   @returns True if subtask containing Transition trans exists.
    */
    bool checkTransitonExists(Transition * trans);
    /**
    *   Checks if condition of transition tr can be changed to cond.
    *   @returns True if no transition from the source state of tr has condition cond.
    */
    bool checkTransCondAvailabe(Transition * tr,ConditionType condType, QString cond);

        //*************     SAVE    ***********//
    /**
    *   Saves the Model to the file filename.
    */
    void save(QString filename);
    /**
    *   Saves the Task G to file FileName, if ifmain==1 saves the paths to other files.
    */
    void printStates(MyGraphType *G, std::string FileName, bool ifMain);
    /**
    *   Checks for errors in the Model.
    *   @returns List of errors.
    */
    QStringList checkIfOK();

        //*************     OTHER   ***********//
    /**
    *   Sets changed parameter and refreshes the TreeView in the main window.
    */
    void setChanged(bool newChanged);
    /**
    *   Getter function to changed.
    */
    bool wasChanged(){return changed;}
    /**
    *   Setter function to block.
    */
    void setBlock(bool block){changeBlocked=block;}

signals:
    /**
    *   Reports error to the main window.
    */
    void reportError(QString);
    /**
    *   Reports a message to main view window.
    */
    void reportMsg(QString);

private:
    /**
    *   pointer to the main window class.
    */
    RESpecTa * res;
    /**
    *   Name of the main task in the model.
    */
    QString mainName;
    /**
    *   Map of all the subtasks.
    */
    std::map<QString, MyGraphType *> * subtasks;
    /**
    *   Folder, to which all the files are saved.
    */
    QString SaveFolder;
    /**
    *   Variable which is checked before load/exit to determine, whether the user should be asked to save his work.
    */
    bool changed;
    /**
    *   Variable which is set to block refreshing the TreeView all the time while loading from file.
    */
    bool changeBlocked;
};

#endif // MODEL_H
