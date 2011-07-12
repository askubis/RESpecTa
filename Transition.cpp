#include <QtGui>

#include "Transition.h"
#include <math.h>

const qreal Pi = 3.14;

Transition::Transition(BaseState *startItem, BaseState *endItem,
         QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(parent, scene)
{
    myStartItem = startItem;
    myEndItem = endItem;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
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
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}

void Transition::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
          QWidget *)
{
    if (myStartItem->collidesWithItem(myEndItem))
        return;

    QPen myPen = pen();
    myPen.setColor(Qt::black);
    if(isSelected())myPen.setColor(Qt::red);
    qreal TransitionSize = 20;
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

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

        QPointF TransitionP1 = line().p1() + QPointF(sin(angle + Pi / 3) * TransitionSize,
                                        cos(angle + Pi / 3) * TransitionSize);
        QPointF TransitionP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * TransitionSize,
                                        cos(angle + Pi - Pi / 3) * TransitionSize);

        TransitionHead.clear();
        TransitionHead << line().p1() << TransitionP1 << TransitionP2;

        painter->drawLine(line());
        painter->drawPolygon(TransitionHead);
}
