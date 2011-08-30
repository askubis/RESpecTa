class BaseState;

#ifndef BaseState_H
#define BaseState_H

#include <QGraphicsPixmapItem>
#include <QList>

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QTextEdit;
class QGraphicsSceneMouseEvent;
class QMenu;
class QGraphicsSceneContextMenuEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QPolygonF;
class QXmlStreamWriter;
class QXmlStreamReader;
QT_END_NAMESPACE

#include "RobotSet.h"
#include "Coordinates.h"
#include <fstream>

class TreeItem;
class Transition;

/**
*   Class being a Base to all the state classes, having only the base attributes of the states.
*/
class BaseState : public QGraphicsPolygonItem
{
public:
    /**
    *   Sets selected and updates graphics view of this object.
    */
    void setSelected(bool selected)
    {
        QGraphicsPolygonItem::setSelected(selected);
        this->update();
    }

    enum { Type = UserType + 15 };

    /**
    *   Getter function to stateType.
    */
    StateType getType() {return stateType;}
    /**
    *   Setter function for stateType.
    */
    void setType(StateType newType){stateType=newType;}
    /**
    *   Getter function to stateName.
    */
    QString getName() {return stateName;}
    /**
    *   Settes function for stateName.
    */
    void setName(QString newName);
    /**
    *   Getter function to argument.
    */
    QString getArgument() {return argument;}
    /**
    *   Setter function for argument.
    */
    void setArgument(QString newArg){argument = newArg;}
    /**
    *   Getter function to parameters.
    */
    QString getParameters() {return parameters;}
    /**
    *   Setter function for parameters.
    */
    void setParameters(QString newParams){parameters = newParams;}
    /**
    *   Getter function for nameTextItem.
    */
    QGraphicsTextItem * getNameTextItem(){return nameTextItem;}
    //void setNameTextItem(QGraphicsTextItem * newItem){nameTextItem=newItem;}

    /**
    *   Getter function for subtaskTransitions.
    */
    QList<Transition*> getSubtaskTransitions(){return subtaskTransitions;}

    /**
    *   Resizes the text in nameTextItem to fit the boundingRect of the state.
    */
    void updateSize();

    /**
    *   Moves the text to fit the left top corner with the state corner.
    */
    void updateTextPositions()
    {
        nameTextItem->setPos(this->pos().x()-50,this->pos().y()-50);
    }

    /**
    *   Loads from XML Stream the data and passes it to the subclasses(if any).
    *   @param  reader Stream from which the data is read
    *   @returns List of errors, which occured while loading
    */
    virtual QStringList LoadFromXML(QXmlStreamReader * reader){return QStringList();}
    /**
    *   Counts how many children does the object have in the TreeView.
    *   @returns Number of children which will be visible in the TreeView
    */
    virtual int itemCount(){return 0;}
    /**
    *   Creates and returns the child of this state located at the index i.
    *   @returns Child of this state at index i.
    */
    virtual TreeItem * getChild(int i, TreeItem * parent){return 0;}


    /**
    *   Function comparing 2 states. Checks only the basic elements of the state(name, type, arguments, parameters).
    *   @returns true if states are equal.
    */
    virtual bool equals(BaseState* other)
    {
        if(getName()==other->getName())
            if(this->stateType==other->stateType)
                if(this->parameters==other->parameters)
                    if(this->argument==other->argument)
                        return true;
        return false;
    }

    /**
    *   Copy operator for BaseState.
    */
    BaseState & operator=(const BaseState &);

    /**
    *   Creates a state with empty nameTextItem and with no stateType.
    */
    BaseState();
    /**
    *   Creates a state, which is a copy of state 'old'.
    */
    BaseState(BaseState& old);

    /**
    *   Deletes nameTextItem, and removes this state from all transitions, which pointed to it as to a subtask.
    */
    virtual ~BaseState();

    /**
    *   Removes the tr Transition from the subtaskTransitions list.
    */
    void removeSubtaskTrans(Transition * tr);
    /**
    *   Adds the Transition tr to the subtaskTransitions list.
    */
    void addSubtaskTrans(Transition * tr);

    /**
    *   Sets context menu for the state.
    */
    void setMenu( QMenu *contextMenu);

    /**
    *   Removes given transition.
    *   @param transition Transition to be removed
    */
    void removeTransition(Transition *transition);
    /**
    *   Removes from both states and deletes all transitions of the given state.
    */
    void removeTransitions();
    /**
    *   Retruns the polygon representing the state.
    */
    QPolygonF polygon() const
        { return myPolygon; }

    /**
    *   Adds transition to the state.
    */
    void addTransition(Transition *transition);

    /**
    *   Returns the image representing the state.
    */
    QPixmap image() const;
    /**
    *   Getter function for Type.
    */
    int type() const
        { return Type;}

    /**
    *   Getter function for Transitions.
    */
    QList<Transition *> getTransitions (){return Transitions;}

    /**
    *   Writes the data of the state to the XML stream.
    *   @param writer Stream to which the data is written
    */
    virtual void Print(QXmlStreamWriter* writer){}

    /**
    *   Creates a string describing the state attributes.
    *   @returns String with the description of the State
    */
    virtual std::string Print()
    {
        std::string x;
        x+="Name ";
        x+=this->stateName.toStdString();
        if(this->getType()<STATE_TYPES_NUMBER)
        {
            x+="\nStateType: ";
            x+=STATE_TYPE_TABLE[this->getType()];
        }
        if(parameters.size()>0)
        {
            x+="\nParameters ";
            x+=this->parameters.toStdString();
        }
        return x;
    }

    /**
    *   Counts the number of transitions which are going out from this state.
    *   @returns Number of transitions starting at this state
    */
    int outTransitionsCount();

protected:
    /**
    *   Opens the context menu for the state.
    */
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    /**
    *   If the change is change of position then updateposition() function is called for allt he transitions of this state.
    */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    /**
    *   Name of the state.
    */
    QString stateName;
    /**
    *   Type of the State.
    */
    StateType stateType;
    /**
    *   Argument(optional) of the state.
    */
    QString argument;
    /**
    *   Parameters(optional) of the state.
    */
    QString parameters;

    /**
    *   TextItem showing name and type of the state.
    */
    QGraphicsTextItem * nameTextItem;

    /**
    *   List of transitions of this state.
    */
    QList<Transition *> Transitions;

    /**
    *   List of transitions, which point to this item as to a subtask.
    */
    QList<Transition *> subtaskTransitions;

private:
    /**
    *   Polygon representing the state.
    */
    QPolygonF myPolygon;
    /**
    *   ContextMenu which is called when right click action has occured.
    */
    QMenu *myContextMenu;

};


#endif

