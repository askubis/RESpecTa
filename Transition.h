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

/**
*   Class representing a transition between the tasks, and it's graphic representation.
*/
class Transition : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4 };

    /**
    *   Getter function for scene.
    */
    QGraphicsScene * getScene(){return scene;}
    /**
    *   Setter function for scene adding this item, all elements of lines vector and subtaskItem.
    */
    void setScene(QGraphicsScene * sc);

    /**
    *   Constructor creating Transition between startItem and EndItem.
    */
    Transition(BaseState *startItem, BaseState *endItem,
      QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    /**
    *   Destructor removing this item from subtask list of the state pointed as subtask and removes this item from scene.
    */
    ~Transition();

    /**
    *   Getter function for CondType.
    */
    ConditionType getCondType(){return CondType;}
    /**
    *   Setter function for CondType.
    */
    void setCondType(ConditionType newCondType){CondType=newCondType;}

    /**
    *   Getter function for type.
    */
    int type() const
        { return Type; }
    /**
    *   Returns QRectf bounding the transition.
    */
    QRectF boundingRect() const;
    /**
    *   Returns the path of the shape of transition.
    */
    QPainterPath shape() const;
    /**
    *   Sets state, which is a start state for this transition.
    */
    void setStartItem( BaseState *newStartItem) { myStartItem=newStartItem; }
    /**
    *   Sets state, which is an end state for this transition
    */
    void setEndItem( BaseState *newEndItem) { myEndItem=newEndItem; }

    /**
    *   Changes the z value (position of overlapping towards other elements).
    */
    void setZValue(qreal z);

    /**
    *   Sets subtask to NULL pointer.
    */
    void removeSubtask()
    {
        subtask=NULL;
    }

    /**
    *   Getter function for myStartItem.
    */
    BaseState *startItem() const
        { return myStartItem; }
    /**
    *   Getter function for myEndItem.
    */
    BaseState *endItem() const
        { return myEndItem; }

    /**
    *   Getter function for condition.
    */
    QString getCondition() {return condition;}
    /**
    *   Setter function for subtask.
    */
    void setCondition(QString newCondition) {condition=newCondition;}
    /**
    *   Getter function for subtask.
    */
    BaseState * getSubtask() {return subtask;}

    /**
    *   Sets new subtask value (state pointer) and removes this transition from the list of pointers of the old state, and adds it to the new state.
    */
    void setSubtask(BaseState * newSubtask)
    {
        if(subtask)subtask->removeSubtaskTrans(this);
        if(subtask)subtaskItem->setPlainText("");
        subtask=newSubtask;
        if(subtask)subtask->addSubtaskTrans(this);

        if(subtask)subtaskItem->setPlainText(QString("Subtask: ").append(subtask->getName()));
    }

    /**
    *   Creates a string describing the coordinates attributes.
    *   @returns String with the description of the Coordinates
    */
    std::string Print()
    {
        std::string toRet;
        toRet+="Condition: ";
        toRet+=CONDITION_TABLE[CondType];
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
        writer->writeAttribute("condition", QString().fromStdString(CONDITION_TABLE[CondType]).append(condition));
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

protected:
    /**
    *	Type of the condition.
    */
    ConditionType CondType;

    /**
    *   Scene on which this item is.
    */
    QGraphicsScene * scene;
    /**
    *   Additional lines usedfor transition whose start and end element are the same.
    */
    std::vector<QGraphicsLineItem *> lines;
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

    /**
    *   GraphicsItem representing name of the State, which is a subtask to this transition.
    */
    QGraphicsTextItem * subtaskItem;
};

#endif
