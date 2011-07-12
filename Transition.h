class Transition;

#ifndef Transition_H
#define Transition_H
#include <QGraphicsLineItem>

#include "baseState.h"
#include "Graph.h"

QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
QT_END_NAMESPACE

//TODO:
//change subtask from QString to BaseState *

//TODO:
//change checkifOK in Model class to check subtask differently.


/**
*   Class representing a transition between the tasks, and it's graphic representation.
*/
class Transition : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4 };

    Transition(BaseState *startItem, BaseState *endItem,
      QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    ~Transition();

    int type() const
        { return Type; }
    QRectF boundingRect() const;
    QPainterPath shape() const;
    /**
    *   Sets state, which is a start state for this transition.
    */
    void setStartItem( BaseState *newStartItem) { myStartItem=newStartItem; }
    /**
    *   Sets state, which is an end state for this transition
    */
    void setEndItem( BaseState *newEndItem) { myEndItem=newEndItem; }

    void removeSubtask(){subtask=NULL;}

    BaseState *startItem() const
        { return myStartItem; }
    BaseState *endItem() const
        { return myEndItem; }

    QString getCondition() {return condition;}
    void setCondition(QString newCondition) {condition=newCondition;}
    BaseState * getSubtask() {return subtask;}

    /**
    *   Sets new subtask value (state pointer) and removes this transition from the list of pointers of the old state, and adds it to the new state.
    */
    void setSubtask(BaseState * newSubtask)
    {
        if(subtask)subtask->removeSubtaskTrans(this);
        subtask=newSubtask;
        if(subtask)subtask->addSubtaskTrans(this);
    }

    /**
    *   Creates a string describing the coordinates attributes.
    *   @returns String with the description of the Coordinates
    */
    std::string Print()
    {
        std::string toRet;
        toRet+="Condition: ";
        toRet+=condition.toStdString();
        if(subtask!=NULL)
        {
            toRet+="\nSubtask: ";
            toRet+=subtask->getName().toStdString();
        }
        return toRet;
    }

    /**
    *   Writes the data of the state to the XML stream.
    *   @param writer Stream to which the data is written
    */
    void Print(QXmlStreamWriter * writer)
    {
        writer->writeStartElement("transition");
        writer->writeAttribute("condition", condition);
        BaseState *tmpState;
        tmpState = endItem();
        QString tmpString;
        if(subtask!=NULL)
        {
              tmpString = subtask->getName();
              tmpString.append(QString(">>")).append(QString(tmpState->getName()));
        }
        else
        {
            tmpString= QString(tmpState->getName());
        }
        writer->writeAttribute("target", tmpString);
        writer->writeEndElement();
    }

protected:
    /**
    *   Paints line, and head of the transition with colour dependent on isSelected().
    */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

public slots:
    /**
    *   Creates new, actual line of the transition.
    */
    void updatePosition();

private:
    /**
    *   Start item of the transition.
    */
    BaseState *myStartItem;
    /**
    *   End item of the transition.
    */
    BaseState *myEndItem;
    /**
    *   Polygon representing the arrowhead of the transition.
    */
    QPolygonF TransitionHead;

    /**
    *   String representing the condition of this transition.
    */
    QString condition;
    /**
    *   Pointer to the subtask starting point of the transition.
    */
    BaseState * subtask;
};

#endif
