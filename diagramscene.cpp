

#include <QtGui>

#include "diagramscene.h"
#include "Transition.h"


DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent,Model * newmod )
    : QGraphicsScene(parent)
{
    mod=newmod;
    myItemMenu = itemMenu;
    myMode = MoveItem;
    //myItemType = BaseState::Step;
    line = 0;
    //textItem = 0;
    //myItemColor = Qt::white;
    //myTextColor = Qt::black;
    //myLineColor = Qt::black;
    //toInsert = new BaseState();
}

/*void DiagramScene::setLineColor(const QColor &color)
{
   /* myLineColor = color;
    if (isItemChange(Transition::Type)) {
        Transition *item =
            qgraphicsitem_cast<Transition *>(selectedItems().first());
        item->setColor(myLineColor);
        update();
    }
}

void DiagramScene::setItemColor(const QColor &color)
{
    /*myItemColor = color;
    if (isItemChange(BaseState::Type)) {
        BaseState *item =
            qgraphicsitem_cast<BaseState *>(selectedItems().first());
        item->setBrush(myItemColor);
    }
}*/

void DiagramScene::setMode(Mode mode)
{
    myMode = mode;
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    QGraphicsTextItem * textItem;
    //BaseState *item;
    switch (myMode) {
        case InsertItem:
            //
            toInsert->setMenu(myItemMenu);
            toInsert->setBrush(Qt::white);
            addItem(toInsert);
            toInsert->setPos(mouseEvent->scenePos());


            //connect(toInsert, SIGNAL(clicked()), this, SIGNAL(itemInserted(BaseState*)));

            textItem = toInsert->getNameTextItem();
            addItem(textItem);
            toInsert->updateTextPositions();
            emit itemInserted(toInsert);
            //textItem->setPos(mouseEvent->scenePos().x()-50, mouseEvent->scenePos().y()-50);
            break;

        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(Qt::black, 2));
            addItem(line);
            break;

    default:
        ;
    }
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

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(this->selectedItems().size()==1 && myMode!=InsertLine)
        {emit itemSelected(selectedItems().first());}

    if (line != 0 && myMode == InsertLine) {
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
            endItems.first()->type() == BaseState::Type &&
            startItems.first() != endItems.first()) {

            BaseState *startItem =
                qgraphicsitem_cast<BaseState *>(startItems.first());
            if(startItem->getName()=="_END_" || startItem->getName()=="_STOP_")
            {
                emit reportError("_END_ and _STOP_ states cannot be a source of transition");
                myMode = MoveItem;
                return;
            }
            BaseState *endItem =
                qgraphicsitem_cast<BaseState *>(endItems.first());
            if(endItem->getName()=="INIT")
            {
                emit reportError("_INIT state cannot be a target of transition");
                myMode = MoveItem;
                return;
            }
            Transition *transition = new Transition(startItem, endItem);
            transition->setCondition(transitionAttributes.first);
            bool test = emit lineInserted(transition);
            if(test)
            {
                transition->setSubtask(transitionAttributes.second);
                transition->setColor(Qt::black);
                startItem->addTransition(transition);
                endItem->addTransition(transition);
                transition->setZValue(-1000.0);
                addItem(transition);
                transition->updatePosition();
                myMode = MoveItem;
                transition->setToolTip(QString().fromStdString(transition->Print()));
                foreach(QGraphicsItem *item, selectedItems())
                {
                    item->setSelected(false);
                }
                selectedItems().clear();
                selectedItems().push_back(transition);
                transition->setSelected(true);
            }
            else
            {

                delete transition;
            }

        }
    }
    line = 0;

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


void DiagramScene::setItemParams(BaseState * toInsert)
{
    toInsert->setMenu(myItemMenu);
    toInsert->setBrush(Qt::white);
    addItem(toInsert);

    QGraphicsTextItem * textItem = toInsert->getNameTextItem();
    addItem(textItem);
    toInsert->updateTextPositions();
    toInsert->updateSize();
}

