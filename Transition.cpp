#include <QtGui>

#include "Transition.h"
#include <math.h>

const qreal Pi = 3.14;

Transition::Transition(BaseState *startItem, BaseState *endItem,
         QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(parent, scene)
{
    subtaskItem = new QGraphicsTextItem();
    CondType=INIFILE;
    subtask=NULL;
    myStartItem = startItem;
    myEndItem = endItem;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));


    lines.push_back(new QGraphicsLineItem(QLineF(0,0,0,0)));
    lines.push_back(new QGraphicsLineItem(QLineF(0,0,0,0)));
    lines.push_back(new QGraphicsLineItem(QLineF(0,0,0,0)));
}

Transition::~Transition()
{
    if(subtask) subtask->removeSubtaskTrans(this);
    scene->removeItem(lines[0]);
    scene->removeItem(lines[1]);
    scene->removeItem(lines[2]);
    scene->removeItem(subtaskItem);
    delete lines[0];
    delete lines[1];
    delete lines[2];
    delete subtaskItem;
}

void Transition::setScene(QGraphicsScene *sc)
{
    scene=sc;
    scene->addItem(lines[0]);
    scene->addItem(lines[1]);
    scene->addItem(lines[2]);
    scene->addItem(subtaskItem);
}

QRectF Transition::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Transition::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(TransitionHead);
    return path;
}

void Transition::updatePosition()
{
    subtaskItem->setPos((myStartItem->x()+myEndItem->x())/2 , (myStartItem->y()+myEndItem->y())/2);
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}

void Transition::setZValue(qreal z)
{
    lines[0]->setZValue(z);
    lines[0]->setZValue(z);
    lines[0]->setZValue(z);
    QGraphicsLineItem::setZValue(z);
}

void Transition::paint(QPainter *painter, const QStyleOptionGraphicsItem * StyleOptions,
          QWidget * widget)
{
    double angle;
    qreal TransitionSize = 20;
    QPointF point1;
    if(myStartItem==myEndItem)
    {
        QPen myPen = pen();
        myPen.setColor(Qt::black);
        if(isSelected())myPen.setColor(Qt::red);
        painter->setPen(myPen);
        painter->setBrush(Qt::black);
        if(isSelected())painter->setBrush(Qt::red);
        QVector<QPoint> pointsVector;
        pointsVector.push_back((startItem()->pos()+QPoint(0,-50)).toPoint());
        pointsVector.push_back((startItem()->pos()+QPoint(0,-100)).toPoint());
        pointsVector.push_back((startItem()->pos()+QPoint(100,-100)).toPoint());
        pointsVector.push_back((startItem()->pos()+QPoint(100,0)).toPoint());
        pointsVector.push_back((startItem()->pos()+QPoint(50,0)).toPoint());
        painter->drawLines(pointsVector);

        setLine(QLineF(startItem()->pos()+QPoint(0,-50), startItem()->pos()+QPoint(0,-100)));

        /*scene->removeItem(lines[0]);
        scene->removeItem(lines[1]);
        scene->removeItem(lines[2]);
        //delete lines[0];
        //delete lines[1];
        //delete lines[2];
        lines.clear();*/



        scene->removeItem(lines[0]);
        scene->removeItem(lines[1]);
        scene->removeItem(lines[2]);
        delete lines[0];
        delete lines[1];
        delete lines[2];
        lines[0]=(new QGraphicsLineItem(QLineF(startItem()->pos()+QPoint(0,-100),startItem()->pos()+QPoint(100,-100))));
        lines[1]=(new QGraphicsLineItem(QLineF(startItem()->pos()+QPoint(100,-100),startItem()->pos()+QPoint(100,0))));
        lines[2]=(new QGraphicsLineItem(QLineF(startItem()->pos()+QPoint(100,0),startItem()->pos()+QPoint(50,0))));
        lines[0]->setZValue(zValue());
        lines[1]->setZValue(zValue());
        lines[2]->setZValue(zValue());
        scene->addItem(lines[0]);
        scene->addItem(lines[1]);
        scene->addItem(lines[2]);

        //lines[0]->setLine((startItem()->pos()+QPoint(0,-100)).x(),(startItem()->pos()+QPoint(0,-100)).y(),(startItem()->pos()+QPoint(100,-100)).x(),(startItem()->pos()+QPoint(100,-100)).y());
        //lines[1]->setLine((startItem()->pos()+QPoint(100,-100)).x(),(startItem()->pos()+QPoint(100,-100)).y(),(startItem()->pos()+QPoint(100,0)).x(),(startItem()->pos()+QPoint(100,0)).y());
        //lines[2]->setLine((startItem()->pos()+QPoint(100,0)).x(),(startItem()->pos()+QPoint(100,0)).y(),(startItem()->pos()+QPoint(50,0)).x(),(startItem()->pos()+QPoint(50,0)).y());


        lines[0]->paint(painter, StyleOptions, widget);
        lines[1]->paint(painter, StyleOptions, widget);
        lines[2]->paint(painter, StyleOptions, widget);


        point1=startItem()->pos()+QPoint(0,-50);
        angle = Pi/2;
    }
    else if (myStartItem->collidesWithItem(myEndItem))
        return;
    else
    {

        QPen myPen = pen();
        myPen.setColor(Qt::black);
        if(isSelected())myPen.setColor(Qt::red);
        painter->setPen(myPen);
        painter->setBrush(Qt::black);
        if(isSelected())painter->setBrush(Qt::red);

        QLineF centerLine(myStartItem->pos(), myEndItem->pos());
        QPolygonF endPolygon = myEndItem->polygon();
        QPointF p1 = endPolygon.first() + myEndItem->pos();
        QPointF p2;
        QPointF intersectPoint;
        QLineF polyLine;
        for (int i = 1; i < endPolygon.count(); ++i) {
        p2 = endPolygon.at(i) + myEndItem->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType =
            polyLine.intersect(centerLine, &intersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
            break;
            p1 = p2;
        }

        setLine(QLineF(intersectPoint, myStartItem->pos()));

        angle = ::acos(line().dx() / line().length());

        if (line().dy() >= 0)
            angle = (Pi * 2) - angle;


        painter->drawLine(line());
        point1=line().p1();

    }


        QPointF TransitionP1 = point1 + QPointF(sin(angle + Pi / 3) * TransitionSize,
                                        cos(angle + Pi / 3) * TransitionSize);
        QPointF TransitionP2 = point1 + QPointF(sin(angle + Pi - Pi / 3) * TransitionSize,
                                        cos(angle + Pi - Pi / 3) * TransitionSize);

        TransitionHead.clear();
        TransitionHead << point1 << TransitionP1 << TransitionP2;

        painter->drawPolygon(TransitionHead);
}
