#ifndef Transition_H
#define Transition_H
class Transition;
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
    QString getSubtask() {return subtask;}
    void setSubtask(QString newSubtask) {subtask=newSubtask;}

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
    QString subtask;
};

#endif
