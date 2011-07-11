#include <QtGui>

#include "baseState.h"
#include "Transition.h"



void BaseState::setName(QString newName)
{
   stateName=newName;
   updateSize();
}

void BaseState::updateSize()
{
    QString x;
    QString y;
    int fontSize = 15;
    do
    {
        y = (QString(this->stateName).append(QString("\n")).append(QString().fromStdString(STATE_TYPE_TABLE[this->stateType])));
        nameTextItem->setPlainText(y);
        QFont tmp = nameTextItem->font();
        tmp.setPixelSize(--fontSize);
        nameTextItem->setFont(tmp);
        while(nameTextItem->boundingRect().width()>100)
        {
            x=y;
            int size = x.size();
            while (nameTextItem->boundingRect().width()>100)
            {
                size--;
                x.truncate(size);
                nameTextItem->setPlainText(x);
            }
        y.insert(size, QString("\n"));
        nameTextItem->setPlainText(y);
        }
    }
    while ((nameTextItem->boundingRect().height()>100));
}

BaseState::BaseState()
{
    myPolygon << QPointF(-50, -50) << QPointF(50, -50)
              << QPointF(50, 50) << QPointF(-50, 50)
              << QPointF(-50, -50);
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    nameTextItem = new QGraphicsTextItem();
}

BaseState & BaseState::operator=(const BaseState &other)
{
    if (this->stateName==other.stateName) return *this;
    this->argument=other.argument;
    this->stateType=other.stateType;
    this->setName(other.stateName);
    this->parameters=other.parameters;
    this->Transitions=other.Transitions;
    this->myContextMenu=other.myContextMenu;
    this->myPolygon=other.myPolygon;
    nameTextItem = new QGraphicsTextItem();
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    return *this;
}

BaseState::BaseState(BaseState& old)
{
    nameTextItem = new QGraphicsTextItem();
    this->argument=old.argument;
    this->stateType=old.stateType;
    this->setName(old.stateName);
    this->parameters=old.parameters;
    myPolygon << QPointF(-50, -50) << QPointF(50, -50)
              << QPointF(50, 50) << QPointF(-50, 50)
              << QPointF(-50, -50);
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void BaseState::setMenu( QMenu *contextMenu)
{
    myContextMenu = contextMenu;
}

void BaseState::removeTransition(Transition *Transition)
{
    int index = Transitions.indexOf(Transition);
    if (index != -1)
        Transitions.removeAt(index);
}

void BaseState::removeTransitions()
{
    foreach (Transition *Transition, Transitions)
    {
        Transition->startItem()->removeTransition(Transition);
        Transition->endItem()->removeTransition(Transition);
        scene()->removeItem(Transition);
        delete Transition;
    }
}

void BaseState::addTransition(Transition *Transition)
{
    Transitions.append(Transition);
}

QPixmap BaseState::image() const
{
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    if(isSelected())pixmap.fill(Qt::red);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    if(isSelected())painter.setPen(QPen(Qt::red, 8));
    painter.translate(125, 125);
    painter.drawPolyline(myPolygon);
    return pixmap;
}

void BaseState::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}

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

int BaseState::outTransitionsCount()
{
    int i=0;
    foreach(Transition* tr, Transitions)
    {
        if(tr->startItem()==this)
            i++;
    }
    return i;
}




