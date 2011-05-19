

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

//! [0]
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
    void setColor(const QColor &color)
        { myColor = color; }
    void setStartItem( BaseState *newStartItem) { myStartItem=newStartItem; }
    void setEndItem( BaseState *newEndItem) { myEndItem=newEndItem; }

    BaseState *startItem() const
        { return myStartItem; }
    BaseState *endItem() const
        { return myEndItem; }

    QString getCondition() {return condition;}
    void setCondition(QString newCondition) {condition=newCondition;}
    std::string getSubtask() {return subtask;}
    void setSubtask(std::string newSubtask) {subtask=newSubtask;}

    //BaseState* getSub() {return sub;}
    //void setSub(BaseState* newSubtask) {sub=newSubtask;}

    std::string Print()
    {
        std::string toRet;
        toRet+="\nCondition: ";
        toRet+=condition.toStdString();
        if(subtask!="")
        {
            toRet+="\nSubtask: ";
            toRet+=subtask;
        }
        return toRet;
    }
    void Print(QXmlStreamWriter * writer)
    {
        writer->writeStartElement("transition");
        writer->writeAttribute("condition", condition);
        BaseState *tmpState;
        tmpState = endItem();
        QString tmpString;
        if(subtask != "")
        {
              tmpString.fromStdString(subtask).append(QString(">>")).append(QString(tmpState->getName()));
        }
        else
        {
            tmpString= QString(tmpState->getName());
        }
        writer->writeAttribute("target", tmpString);
        writer->writeEndElement();
    }


public slots:
    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

private:
    BaseState *myStartItem;
    BaseState *myEndItem;
    QColor myColor;
    QPolygonF TransitionHead;

    QString condition;
    std::string subtask;
};
//! [0]

#endif
