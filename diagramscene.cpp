

#include <QtGui>

#include "diagramscene.h"
#include "Transition.h"

//! [0]
DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    //myItemType = BaseState::Step;
    line = 0;
    //textItem = 0;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;
    //toInsert = new BaseState();
}
//! [0]

//! [1]
void DiagramScene::setLineColor(const QColor &color)
{
    myLineColor = color;
    if (isItemChange(Transition::Type)) {
        Transition *item =
            qgraphicsitem_cast<Transition *>(selectedItems().first());
        item->setColor(myLineColor);
        update();
    }
}
//! [1]

//! [2]
/*void DiagramScene::setTextColor(const QColor &color)
{
    myTextColor = color;
    if (isItemChange(DiagramTextItem::Type)) {
        DiagramTextItem *item =
            qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        item->setDefaultTextColor(myTextColor);
    }
}*/
//! [2]

//! [3]
void DiagramScene::setItemColor(const QColor &color)
{
    myItemColor = color;
    if (isItemChange(BaseState::Type)) {
        BaseState *item =
            qgraphicsitem_cast<BaseState *>(selectedItems().first());
        item->setBrush(myItemColor);
    }
}
//! [3]

//! [4]
/*void DiagramScene::setFont(const QFont &font)
{
    myFont = font;

    if (isItemChange(DiagramTextItem::Type)) {
        QGraphicsTextItem *item =
            qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        //At this point the selection can change so the first selected item might not be a DiagramTextItem
        if (item)
            item->setFont(myFont);
    }
}*/
//! [4]

void DiagramScene::setMode(Mode mode)
{
    myMode = mode;
}

/*void DiagramScene::setItemType(BaseState::DiagramType type)
{
    myItemType = type;
}*/

//! [5]
/*void DiagramScene::editorLostFocus(DiagramTextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
}*/
//! [5]

//! [6]
void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    //BaseState *item;
    switch (myMode) {
        case InsertItem:
            //
            toInsert->setMenu(myItemMenu);
            toInsert->setBrush(myItemColor);
            addItem(toInsert);
            toInsert->setPos(mouseEvent->scenePos());
            emit itemInserted(toInsert);
            break;
//! [6] //! [7]
        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(myLineColor, 2));
            addItem(line);
            break;
//! [7] //! [8]
        /*case InsertText:
            textItem = new DiagramTextItem();
            textItem->setFont(myFont);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setZValue(1000.0);
            connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                    this, SLOT(editorLostFocus(DiagramTextItem*)));
            connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                    this, SIGNAL(itemSelected(QGraphicsItem*)));
            addItem(textItem);
            textItem->setDefaultTextColor(myTextColor);
            textItem->setPos(mouseEvent->scenePos());
            emit textInserted(textItem);*/
//! [8] //! [9]
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}
//! [9]

//! [10]
void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}
//! [10]

//! [11]
void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != 0 && myMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;
//! [11] //! [12]



        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first()->type() == BaseState::Type &&
            endItems.first()->type() == BaseState::Type &&
            startItems.first() != endItems.first()) {
            BaseState *startItem =
                qgraphicsitem_cast<BaseState *>(startItems.first());
            BaseState *endItem =
                qgraphicsitem_cast<BaseState *>(endItems.first());
            Transition *transition = new Transition(startItem, endItem);
            bool test = emit lineInserted(transition);
            if(test)
            {
                transition->setCondition(transitionAttributes.first);
                //transition->setSubtask(transitionAttributes.second);//to be changed
                transition->setColor(myLineColor);
                startItem->addTransition(transition);
                endItem->addTransition(transition);
                transition->setZValue(-1000.0);
                addItem(transition);
                transition->updatePosition();
            }
            else
            {

                delete transition;
            }

        }
    }
//! [12] //! [13]
    line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
//! [13]

//! [14]
bool DiagramScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}
//! [14]
