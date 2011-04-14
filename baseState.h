
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
QT_END_NAMESPACE

#include "RobotSet.h"
#include "Coordinates.h"
#include <fstream>


class Transition;

//! [0]
class BaseState : public QGraphicsPolygonItem
{
public:

    enum { Type = UserType + 15 };

    StateType getType() {return stateType;}
    void setType(StateType newType){stateType=newType;}
    std::string getName() {return stateName;}
    void setName(std::string newName);
    int getArgument() {return argument;}
    void setArgument(int newArg){argument = newArg;}
    std::string getParameters() {return parameters;}
    void setParameters(std::string newParams){parameters = newParams;}
    QGraphicsTextItem * getNameTextItem(){return nameTextItem;}
    void setNameTextItem(QGraphicsTextItem * newItem){nameTextItem=newItem;}
    void setSubtaskName (std::string newSubName){ subtaskName = newSubName;updateSize();}

    void updateTextPositions()
    {
        nameTextItem->setPos(this->pos().x()-50,this->pos().y()-50);
    }


  //  enum DiagramType { Step, Conditional, StartEnd, Io };

    BaseState & operator =(const BaseState &);

    BaseState();

    BaseState(BaseState& old);

    ~BaseState(){delete nameTextItem;}

    void setMenu( QMenu *contextMenu);

    void removeTransition(Transition *transition);
    void removeTransitions();
   /* DiagramType diagramType() const
        { return myDiagramType; }*/
    QPolygonF polygon() const
        { return myPolygon; }
    void addTransition(Transition *transition);
    QPixmap image() const;
    int type() const
        { return Type;}

    QList<Transition *> getTransitions (){return Transitions;}

    virtual std::string Print()
    {
        std::string x;
        x+="\nName ";
        x+=this->getName();
        x+="\nStateType: ";
        x+=STATE_TYPE_TABLE[this->getType()];
        x+="\nParameters ";
        x+=this->getParameters();
    }

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    void updateSize();

   // DiagramType myDiagramType;
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Transition *> Transitions;


    std::string stateName;
    std::string subtaskName;
    StateType stateType;
    int argument;
    std::string parameters;

    QGraphicsTextItem * nameTextItem;



};
//! [0]

#endif

