class TreeItem;
class TreeStateItem;
class TreeTransItem;
class TreeCoordItem;
class TreePoseItem;
class TreeInitItem;
class TreeRobotSetItem;
class TreeTextItem;
class TreeGraphItem;

#ifndef TREEITEM_H
#define TREEITEM_H

#include "TreeModel.h"

#include <QHash>
#include "Transition.h"
#include "Coordinates.h"
#include "Pose.h"
#include "robotInit.h"
#include "RobotSet.h"

/**
*   Base class of item of the TreeView.
*/
class TreeItem
{
public:
    /**
    *   Creates an item with given parent, and saves the row value.
    */
    TreeItem( int row, TreeItem *parent = 0);
    /**
    *   Destructor for base item.
    */
    ~TreeItem();
    /**
    *   Returns parent of this element.
    */
    TreeItem *parent();
    /**
    *   Returns number of the row in that level (considering only children of parent of this element) on which this element is.
    */
    int row();
    /**
    *   Getter function for Type.
    */
    int getType(){return Type;}
    /**
    *   Returns number of children, which this item has.
    */
    virtual int childNodesCount(){return 0;}
    /**
    *   Returns name (1st column value) for this element.
    */
    virtual QString Name(){return QString();}
    /**
    *   Returns Value (2nd column value) for this element.
    */
    virtual QString Attr(){return QString();}
    /**
    *   Returns the i-th child of this element.
    */
    virtual TreeItem *child(int i){return NULL;}

    /**
    *   Returns the first met graphicsItem while going up the item tree.
    */
    virtual QGraphicsItem * getGraphicsItem(){return NULL;}


protected:
    /**
    *   Type of the item.
    */
    int Type;
    /**
    *   Table of items, used to store items, not to create them with every use of child(i).
    */
    QHash<int,TreeItem*> childItems;
    /**
    *   Parentitem of this element.
    */
    TreeItem *parentItem;
    /**
    *   Number of the row, in which this item is in the list of the children of parentelement.
    */
    int rowNumber;
};

/**
*   Item of the treeview, which represents a State (uses it's name and StateType).
*/
class TreeStateItem : public TreeItem
{
public:
    /**
    *   Creates an item with given parent, and saves the row value.
    */
    TreeStateItem( int row, TreeItem *parent = 0):TreeItem(row, parent){}
    /**
    *   Destructor of the item.
    */
    ~TreeStateItem(){}

    /**
    *   Sets State which is represented by this item.
    */
    void setState(BaseState * st){Type = 0; state = st;}
    /**
    *   Returns the first met graphicsItem while going up the item tree.
    */
    QGraphicsItem * getGraphicsItem(){return state;}
    /**
    *   Returns number of children, which this item has.
    */
    int childNodesCount(){return state->itemCount();}
    /**
    *   Returns the i-th child of this element.
    */
    TreeItem *child(int i);

    /**
    *   Returns name (1st column value) for this element.
    */
    QString Name(){return state->getName();}
    /**
    *   Returns Value (2nd column value) for this element.
    */
    QString Attr(){return QString().fromStdString(STATE_TYPE_TABLE[state->getType()]);}
private:
    /**
    *   State represented by this item.
    */
    BaseState * state;//0
};

/**
*   Item of the treeview, which represents a Transition.
*/
class TreeTransItem : public TreeItem
{
public:
    /**
    *   Creates an item with given parent, and saves the row value.
    */
    TreeTransItem( int row, TreeItem *parent = 0):TreeItem(row, parent){}
    /**
    *   Destructor of the item.
    */
    ~TreeTransItem(){}

    /**
    *   Sets Transition, which is represented by this item.
    */
    void setTrans(Transition * _tr){Type = 1; tr = _tr;}
    /**
    *   Returns the first met graphicsItem while going up the item tree.
    */
    QGraphicsItem * getGraphicsItem(){return tr;}
    /**
    *   Returns number of children, which this item has.
    */
    int childNodesCount(){if(tr->getSubtask()!=NULL)return 1; else return 0;}
    /**
    *   Returns the i-th child of this element.
    */
    TreeItem *child(int i);

    /**
    *   Returns name (1st column value) for this element.
    */
    QString Name(){return QString("->")+=QString().fromStdString(CONDITION_TABLE[tr->getCondType()]).append(tr->getCondition());}
    /**
    *   Returns Value (2nd column value) for this element.
    */
    QString Attr(){return tr->endItem()->getName();}
private:
    /**
    *   Transition represented by this item.
    */
    Transition * tr;//1
};

/**
*   Item of the treeview, which represents Coordinates.
*/
class TreeCoordItem : public TreeItem
{
public:
    /**
    *   Creates an item with given parent, and saves the row value.
    */
    TreeCoordItem( int row, TreeItem *parent = 0):TreeItem(row, parent){}
    /**
    *   Destructor of the item.
    */
    ~TreeCoordItem(){}

    /**
    *   Sets coordinates, which are represented by this item.
    */
    void setCoords(Coordinates * _coords){Type = 2; coords = _coords;}
    /**
    *   Returns the first met graphicsItem while going up the item tree.
    */
    QGraphicsItem * getGraphicsItem(){return parentItem->getGraphicsItem();}
    /**
    *   Returns number of children, which this item has.
    */
    int childNodesCount()
    {
        int i=0;
        if(isProper(coords->getMotionType()))
            i++;
        if(isProper(coords->getCoordType()))
            i++;

        i+=coords->getPoses().size();
        return i;
    }
    /**
    *   Returns the i-th child of this element.
    */
    TreeItem *child(int i);

    /**
    *   Returns name (1st column value) for this element.
    */
    QString Name(){return QString("Coordinates");}
    /**
    *   Returns Value (2nd column value) for this element.
    */
    QString Attr(){return QString();}
private:
    /**
    *   Coordinates, which are represented byy this item.
    */
    Coordinates * coords;//2
};

/**
*   Item of the treeview, which represents a RobotSet.
*/
class TreeRobotSetItem : public TreeItem
{
public:
    /**
    *   Creates an item with given parent, and saves the row value.
    */
    TreeRobotSetItem( int row, TreeItem *parent = 0):TreeItem(row, parent){}
    /**
    *   Destructor of the item.
    */
    ~TreeRobotSetItem(){}

    /**
    *   Sets set, which is represented by this item, also defines if it's first or second set.
    */
    void setSet(std::vector<Robot> _set){Type = 3; set = _set;}
    /**
    *   Returns number of children, which this item has.
    */
    int childNodesCount(){return set.size();}
    /**
    *   Returns the i-th child of this element.
    */
    TreeItem *child(int i);
    /**
    *   Returns the first met graphicsItem while going up the item tree.
    */
    QGraphicsItem * getGraphicsItem(){return parentItem->getGraphicsItem();}

    /**
    *   Returns name (1st column value) for this element.
    */
    QString Name(){return "FirstSet";}
    /**
    *   Returns Value (2nd column value) for this element.
    */
    QString Attr(){return QString();}
private:

    /**
    *   Set, which is represented by this item.
    */
    std::vector<Robot> set;//3
};


/**
*   Item of the treeview, which represents a robotInit.
*/
class TreeInitItem : public TreeItem
{
public:
    /**
    *   Creates an item with given parent, and saves the row value.
    */
    TreeInitItem( int row, TreeItem *parent = 0):TreeItem(row, parent){}
    /**
    *   Destructor of the item.
    */
    ~TreeInitItem(){}

    /**
    *   Sets robotInit which is represented by this item.
    */
    void setInit(robotInit _init){Type = 4; init = _init;}
    /**
    *   Returns number of children, which this item has.
    */
    int childNodesCount(){return init.init_values.size();}
    /**
    *   Returns the i-th child of this element.
    */
    TreeItem *child(int i);
    /**
    *   Returns the first met graphicsItem while going up the item tree.
    */
    QGraphicsItem * getGraphicsItem(){return parentItem->getGraphicsItem();}

    /**
    *   Returns name (1st column value) for this element.
    */
    QString Name(){return QString("Init");}
    /**
    *   Returns Value (2nd column value) for this element.
    */
    QString Attr(){return QString().fromStdString(ROBOT_TABLE[init.robot]);}
private:
    /**
    *   RobotInit, which is represented by this state.
    */
    robotInit init;//4
};

/**
*   Item of the treeview, which represents a Pose.
*/
class TreePoseItem : public TreeItem
{
public:
    /**
    *   Creates an item with given parent, and saves the row value.
    */
    TreePoseItem( int row, TreeItem *parent = 0):TreeItem(row, parent){}
    /**
    *   Destructor of the item.
    */
    ~TreePoseItem(){}

    /**
    *   Sets pose, which is represented by this item.
    */
    void setPos(Pose * _pos){Type = 5; pos = _pos;}
    /**
    *   Returns number of children, which this item has.
    */
    int childNodesCount(){return 3;}
    /**
    *   Returns the i-th child of this element.
    */
    TreeItem *child(int i);
    /**
    *   Returns the first met graphicsItem while going up the item tree.
    */
    QGraphicsItem * getGraphicsItem(){return parentItem->getGraphicsItem();}

    /**
    *   Returns name (1st column value) for this element.
    */
    QString Name(){return QString("Pose");}
    /**
    *   Returns Value (2nd column value) for this element.
    */
    QString Attr()
    {
        return QString();
    }
private:
    /**
    *   Pose, which is represented by this item.
    */
    Pose * pos;//5
};

/**
*   Item of the treeview, which represents various items without children.
*/
class TreeTextItem : public TreeItem
{
public:
    /**
    *   Creates an item with given parent, and saves the row value.
    */
    TreeTextItem( int row, TreeItem *parent = 0):TreeItem(row, parent){}
    /**
    *   Destructor of the item.
    */
    ~TreeTextItem(){}

    /**
    *   Sets name and value, which are represented by this value.
    */
    void setNameAttr(QString _name, QString _attr){Type = 100; name=_name; attr=_attr;}
    /**
    *   Returns number of children, which this item has.
    */
    int childNodesCount(){return 0;}
    /**
    *   Returns the i-th child of this element.
    */
    TreeItem *child(int i)
    {return 0;}
    /**
    *   Returns the first met graphicsItem while going up the item tree.
    */
    QGraphicsItem * getGraphicsItem(){return parentItem->getGraphicsItem();}

    /**
    *   Returns name (1st column value) for this element.
    */
    QString Name(){return name;}
    /**
    *   Returns Value (2nd column value) for this element.
    */
    QString Attr(){return attr;}
private:
    /**
    *   Name (1st column value) for this item.
    */
    QString name;
    /**
    *   Attribute (2nd column value) for this item.
    */
    QString attr;
};

/**
*   Item of the treeview, which represents a Graph; it's a parent to all other items of the TreeView.
*/
class TreeGraphItem : public TreeItem
{
public:
    /**
    *   Creates an item with given parent, and saves the row value.
    */
    TreeGraphItem( int row,  TreeItem *parent = 0):TreeItem(row, parent){}
    /**
    *   Destructor of the item.
    */
    ~TreeGraphItem(){}

    /**
    *   Sets Graph, which is represented by this item and sets TreeModel, which is used to get list of states of this Graph.
    */
    void setGraph(MyGraphType * _gr, TreeModel * mod){Type=101;gr=_gr;Model=mod;}
    /**
    *   Returns number of children, which this item has.
    */
    int childNodesCount(){return boost::num_vertices(*gr);}
    /**
    *   Returns the i-th child of this element.
    */
    TreeItem *child(int i);
    /**
    *   Returns the first met graphicsItem while going up the item tree.
    */
    QGraphicsItem * getGraphicsItem(){return NULL;}

    /**
    *   Returns name (1st column value) for this element.
    */
    QString Name(){return QString();}
    /**
    *   Returns Value (2nd column value) for this element.
    */
    QString Attr(){return QString();}

private:
    /**
    *   Graph, which is represented by this item;
    */
    MyGraphType * gr;//101
    /**
    *   Model of the tree, which is used to get list of state names form the project model.
    */
    TreeModel * Model;
};

#endif // TREEITEM_H
