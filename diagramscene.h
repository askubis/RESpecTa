
#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include "baseState.h"
#include "Graph.h"

class Model;

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE


class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

    DiagramScene(QMenu *itemMenu, QObject *parent,Model * newmod );
    /*QFont font() const
        { return myFont; }
    QColor textColor() const
        { return myTextColor; }
    QColor itemColor() const
        { return myItemColor; }
    QColor lineColor() const
        { return myLineColor; }*/
    void setLineColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setItemColor(const QColor &color);
    void setToInsertState (BaseState * newState){toInsert = newState;}
    void setTransitionAttributes(std::pair<QString,QString> thePair){transitionAttributes=thePair;}
    void setItemParams(BaseState * toInsert);

public slots:
    void setMode(Mode mode);

signals:
    void itemInserted(BaseState *item);
    bool lineInserted(Transition * line);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);
    void reportError(QString);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    Model * mod;

    std::pair<QString,QString> transitionAttributes;
    BaseState * toInsert;
    QMenu *myItemMenu;
    Mode myMode;
    QPointF startPoint;
    QGraphicsLineItem *line;
};

#endif
