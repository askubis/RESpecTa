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

class Transition : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4 };

    Transition(BaseState *startItem, BaseState *endItem,
      QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    int type() const
        { return Type; }
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setStartItem( BaseState *newStartItem) { myStartItem=newStartItem; }
    void setEndItem( BaseState *newEndItem) { myEndItem=newEndItem; }

    BaseState *startItem() const
        { return myStartItem; }
    BaseState *endItem() const
        { return myEndItem; }

    QString getCondition() {return condition;}
    void setCondition(QString newCondition) {condition=newCondition;}
    QString getSubtask() {return subtask;}
    void setSubtask(QString newSubtask) {subtask=newSubtask;}

    /**
    *   Creates a string describing the coordinates attributes.
    *   @returns String with the description of the Coordinates
    */
    std::string Print()
    {
        std::string toRet;
        toRet+="Condition: ";
        toRet+=condition.toStdString();
        if(subtask!="")
        {
            toRet+="\nSubtask: ";
            toRet+=subtask.toStdString();
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
        if(subtask != "")
        {
              tmpString = subtask;
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
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

public slots:
    void updatePosition();

private:
    BaseState *myStartItem;
    BaseState *myEndItem;
    QPolygonF TransitionHead;

    QString condition;
    QString subtask;
};

#endif
