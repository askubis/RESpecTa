#include <QtGui>

#include "diagramscene.h"
#include "Transition.h"


DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent,Model * newmod )
    : QGraphicsScene(parent)
{
    mod=newmod;
    myItemMenu = itemMenu;
    myMode = MoveItem;
    line = 0;
}

void DiagramScene::setMode(SceneMode mode)
{
    myMode = mode;
    emit modeChanged(mode);
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    QGraphicsTextItem * textItem;
    switch (myMode) {
        case InsertItem:
            toInsert->setMenu(myItemMenu);
            toInsert->setBrush(Qt::white);
            addItem(toInsert);
            toInsert->setPos(mouseEvent->scenePos());

            textItem = toInsert->getNameTextItem();
            addItem(textItem);
            toInsert->updateTextPositions();
            emit itemInserted(toInsert);
            break;

        case InsertLine:

            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(Qt::black, 2));
            addItem(line);
            if(items(line->line().p1()).size()==0)
            {
                emit LineCanceled();
                delete line;
                return;
            }
            break;
    default:
        break;
    }
    emit selectionChanged();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        foreach (QGraphicsItem *item, this->selectedItems())
        {
            if (item->type() == BaseState::Type)
            {
                BaseState * tmp = (BaseState *)item;
                tmp->updateTextPositions();
            }
        }
    }
}
int max(int a, qreal b)
{
    return a>b?a:b;
}

int min(int a, qreal b)
{
    return a<b?a:b;
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(this->selectedItems().size()==1 && myMode!=InsertLine)
        {emit itemSelected(selectedItems().first());}

    if (line != 0 && myMode == InsertLine)
    {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

        while(startItems.count()>1 && startItems.first()->type() != BaseState::Type)
        {
            startItems.removeFirst();
        }
        while(endItems.count()>1 && endItems.first()->type() != BaseState::Type)
        {
            endItems.removeFirst();
        }

        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first()->type() == BaseState::Type &&
            endItems.first()->type() == BaseState::Type) {

            BaseState *startItem =
                qgraphicsitem_cast<BaseState *>(startItems.first());
            if(startItem->getName()=="_END_" || startItem->getName()=="_STOP_")
            {
                emit reportError("_END_ and _STOP_ states cannot be a source of transition");
                emit LineCanceled();
                return;
            }
            BaseState *endItem =
                qgraphicsitem_cast<BaseState *>(endItems.first());
            if(endItem->getName()=="INIT")
            {
                emit reportError("_INIT state cannot be a target of transition");
                emit LineCanceled();
                return;
            }
            Transition *transition = new Transition(startItem, endItem);
            transition->setCondition(transitionAttributes.first);
            transition->setSubtask(mod->getState(transitionAttributes.second));
            transition->setScene(this);
            emit lineInserted(transition);

            startItem->addTransition(transition);
            if(startItem!=endItem)endItem->addTransition(transition);
            transition->setZValue(-1000.0);
            addItem(transition);
            transition->updatePosition();
            setMode(MoveItem);
            transition->setToolTip(QString().fromStdString(transition->Print()));
            foreach(QGraphicsItem *item, selectedItems())
            {
                item->setSelected(false);
            }
            selectedItems().clear();
            selectedItems().push_back(transition);
            transition->setSelected(true);
            emit itemSelected(transition);
        }
    }
    line = 0;

    QGraphicsScene::mouseReleaseEvent(mouseEvent);

    if(this->myMode==MoveItem)
    {
        foreach(QGraphicsItem * it, this->selectedItems())
        {
            if (it->type()==BaseState::Type)
            {
                checkIfFits((BaseState *)it);
            }
        }
    }
}

void DiagramScene::checkIfFits(BaseState * it)
{
    if ((! this->sceneRect().contains(it->pos()-QPoint(50,50))) || (! this->sceneRect().contains(it->pos()+QPoint(50,50))))
    setSceneRect(QRectF(
                     min(0, it->pos().x() -50),
                     min(0, it->pos().y() -50),
                     max(5000, it->pos().x()+50),
                     max(5000, it->pos().y())+50));
}

void DiagramScene::setItemParams(BaseState * toInsert)
{
    toInsert->setMenu(myItemMenu);
    toInsert->setBrush(Qt::white);
    addItem(toInsert);
    checkIfFits(toInsert);

    QGraphicsTextItem * textItem = toInsert->getNameTextItem();
    addItem(textItem);
    toInsert->updateTextPositions();
    toInsert->updateSize();
}

