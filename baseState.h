
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


class Transition;
class StateWidget;

class BaseState : public QGraphicsPolygonItem
{
public:

    enum { Type = UserType + 15 };



    StateType getType() {return stateType;}
    void setType(StateType newType){stateType=newType;}
    QString getName() {return stateName;}
    void setName(QString newName);
    int getArgument() {return argument;}
    void setArgument(int newArg){argument = newArg;}
    QString getParameters() {return parameters;}
    void setParameters(QString newParams){parameters = newParams;}
    QGraphicsTextItem * getNameTextItem(){return nameTextItem;}
    void setNameTextItem(QGraphicsTextItem * newItem){nameTextItem=newItem;}
    //void setSubtaskName (QString newSubName){ subtaskName = newSubName;updateSize();}
    void updateSize();

    void updateTextPositions()
    {
        nameTextItem->setPos(this->pos().x()-50,this->pos().y()-50);
    }
    virtual QStringList LoadFromXML(QXmlStreamReader *){}


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

    virtual void Print(QXmlStreamWriter* ){}
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

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:


   // DiagramType myDiagramType;
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Transition *> Transitions;

protected:

    QString stateName;
    //QString subtaskName;
    StateType stateType;
    int argument;
    QString parameters;

    QGraphicsTextItem * nameTextItem;



};


#endif

