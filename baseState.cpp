
#include <QtGui>

#include "baseState.h"
#include "arrow.h"


BaseState & BaseState::operator=(const BaseState &other)
{
    if (this->stateName==other.stateName) return *this;//TODO:askubis check if not wrong with that condition
    this->argument=other.argument;
    this->stateName=other.stateName;
    this->stateType=other.stateType;
    this->parameters=other.parameters;
    this->arrows=other.arrows;
    this->myContextMenu=other.myContextMenu;
    this->myPolygon=other.myPolygon;
    return *this;
}

BaseState::BaseState(BaseState& old)
{
    this->argument=old.argument;
    this->stateName=old.stateName;
    this->stateType=old.stateType;
    this->parameters=old.parameters;
}

//! [0]
BaseState::BaseState( QMenu *contextMenu,
             QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsPolygonItem(parent, scene)
{
    //myDiagramType = diagramType;
    myContextMenu = contextMenu;

    //QPainterPath path;
            myPolygon << QPointF(-100, -100) << QPointF(100, -100)
                      << QPointF(100, 100) << QPointF(-100, 100)
                      << QPointF(-100, -100);
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}
//! [0]

//! [1]
void BaseState::removeArrow(Arrow *arrow)
{
    int index = arrows.indexOf(arrow);

    if (index != -1)
        arrows.removeAt(index);
}
//! [1]

//! [2]
void BaseState::removeArrows()
{
    foreach (Arrow *arrow, arrows) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}
//! [2]

//! [3]
void BaseState::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}
//! [3]

//! [4]
QPixmap BaseState::image() const
{
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    painter.translate(125, 125);
    painter.drawPolyline(myPolygon);

    return pixmap;
}
//! [4]

//! [5]
void BaseState::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}
//! [5]

//! [6]
QVariant BaseState::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (Arrow *arrow, arrows) {
            arrow->updatePosition();
        }
    }

    return value;
}
//! [6]
