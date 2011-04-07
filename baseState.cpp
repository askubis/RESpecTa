
#include <QtGui>

#include "baseState.h"
#include "Transition.h"


BaseState::BaseState()
{
    myPolygon << QPointF(-50, -50) << QPointF(50, -50)
              << QPointF(50, 50) << QPointF(-50, 50)
              << QPointF(-50, -50);
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

BaseState & BaseState::operator=(const BaseState &other)
{
    if (this->stateName==other.stateName) return *this;//TODO:askubis check if not wrong with that condition
    this->argument=other.argument;
    this->stateName=other.stateName;
    this->stateType=other.stateType;
    this->parameters=other.parameters;
    this->Transitions=other.Transitions;
    this->myContextMenu=other.myContextMenu;
    this->myPolygon=other.myPolygon;
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    return *this;
}

BaseState::BaseState(BaseState& old)
{
    this->argument=old.argument;
    this->stateName=old.stateName;
    this->stateType=old.stateType;
    this->parameters=old.parameters;
    myPolygon << QPointF(-50, -50) << QPointF(50, -50)
              << QPointF(50, 50) << QPointF(-50, 50)
              << QPointF(-50, -50);
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

//! [0]
void BaseState::setMenu( QMenu *contextMenu)

{
    myContextMenu = contextMenu;

}
//! [0]

//! [1]
void BaseState::removeTransition(Transition *Transition)
{
    int index = Transitions.indexOf(Transition);

    if (index != -1)
        Transitions.removeAt(index);
}
//! [1]

//! [2]
void BaseState::removeTransitions()
{
    foreach (Transition *Transition, Transitions) {
        Transition->startItem()->removeTransition(Transition);
        Transition->endItem()->removeTransition(Transition);
        scene()->removeItem(Transition);
        delete Transition;
    }
}
//! [2]

//! [3]
void BaseState::addTransition(Transition *Transition)
{
    Transitions.append(Transition);
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
        foreach (Transition *Transition, Transitions) {
            Transition->updatePosition();
        }
    }

    return value;
}
//! [6]



