#ifndef TREEITEM_H
#define TREEITEM_H

class TreeItem;
class TreeStateItem;
class TreeTransItem;
class TreeCoordItem;
class TreePoseItem;
class TreeInitItem;
class TreeRobotSetItem;
class TreeTextItem;
class TreeGraphItem;

#include "TreeModel.h"

//#include <QDomNode>
#include <QHash>
//#include "baseState.h"
class BaseState;
#include "Transition.h"
#include "Coordinates.h"
#include "Pose.h"
#include "genInit.h"
#include "RobotSet.h"

class TreeItem
{
public:
    TreeItem( int row, TreeModel *mod, TreeItem *parent = 0);
    ~TreeItem();
    TreeItem *parent();
    int row();
    TreeModel * getModel(){return Model;}
    int getType(){return Type;}
    virtual int childNodesCount(){}
    virtual QString Name(){}
    virtual QString Attr(){}
    virtual TreeItem *child(int i){}

    int Type;//TODO change
protected:
    QHash<int,TreeItem*> childItems;
    TreeItem *parentItem;
    int rowNumber;
    TreeModel * Model;
};

class TreeStateItem : public TreeItem
{
public:
    TreeStateItem( int row, TreeModel * mod,  TreeItem *parent = 0):TreeItem(row, mod, parent){}
    ~TreeStateItem(){}

    void setState(BaseState * st){Type = 0; state = st;}
    BaseState * getState(){return state;}
    int childNodesCount(){return state->itemCount();}
    TreeItem *child(int i);

    QString Name(){return state->getName();}
    QString Attr(){return QString().fromStdString(STATE_TYPE_TABLE[state->getType()]);}
private:
    BaseState * state;//0
};

class TreeTransItem : public TreeItem
{
public:
    TreeTransItem( int row, TreeModel * mod,  TreeItem *parent = 0):TreeItem(row, mod, parent){}
    ~TreeTransItem(){}

    void setTrans(Transition * _tr){Type = 1; tr = _tr;}
    int childNodesCount(){if(tr->getSubtask().size()>0)return 1; else return 0;}
    TreeItem *child(int i);

    QString Name(){return QString("->")+=tr->getCondition();}
    QString Attr(){return tr->endItem()->getName();}
private:
    Transition * tr;//{return 0;}
};

class TreeCoordItem : public TreeItem
{
public:
    TreeCoordItem( int row, TreeModel * mod,  TreeItem *parent = 0):TreeItem(row, mod, parent){}
    ~TreeCoordItem(){}

    void setCoords(Coordinates * _coords){Type = 2; coords = _coords;}
    int childNodesCount()
    {
        int i=0;
        if(coords->getMotionType()>=0&&coords->getMotionType()<MOTIONTYPES_NUMBER)
            i++;
        if(coords->getCoordType()>=0&&coords->getCoordType()<COORDTYPES_NUMBER)
            i++;

        i+=coords->getPoses().size();
        return i;
    }//check boundaries
    TreeItem *child(int i);

    QString Name(){return QString("Coordinates");}
    QString Attr(){return QString();}
private:
    Coordinates * coords;//2
};

class TreeRobotSetItem : public TreeItem
{
public:
    TreeRobotSetItem( int row, TreeModel * mod,  TreeItem *parent = 0):TreeItem(row, mod, parent){}
    ~TreeRobotSetItem(){}

    void setSet(std::vector<Robot> _set,bool _first){Type = 3; set = _set;first=_first;}
    int childNodesCount(){return set.size();}
    TreeItem *child(int i);

    QString Name(){if(first)return "FirstSet";else return "SecSet";}
    QString Attr(){return QString();}
private:

    std::vector<Robot> set;//3
    bool first;//true=first, false=second
};

class TreeInitItem : public TreeItem
{
public:
    TreeInitItem( int row, TreeModel * mod,  TreeItem *parent = 0):TreeItem(row, mod, parent){}
    ~TreeInitItem(){}

    void setInit(genInit _init){Type = 4; init = _init;}
    int childNodesCount(){return init.init_values.size();}
    TreeItem *child(int i);

    QString Name(){return QString("Init");}
    QString Attr(){return QString().fromStdString(ROBOT_TABLE[init.robot]);}
private:
    genInit init;//4
};

class TreePoseItem : public TreeItem
{
public:
    TreePoseItem( int row, TreeModel * mod,  TreeItem *parent = 0):TreeItem(row, mod, parent){}
    ~TreePoseItem(){}

    void setPos(Pose * _pos){Type = 5; pos = _pos;}
    int childNodesCount(){return 3;}
    TreeItem *child(int i);

    QString Name(){return QString();}
    QString Attr(){return QString();}
private:
    Pose * pos;//5
};



class TreeTextItem : public TreeItem
{
public:
    TreeTextItem( int row, TreeModel * mod,  TreeItem *parent = 0):TreeItem(row, mod, parent){}
    //~TreeTextItem(){}

    void setNameAttr(QString _name, QString _attr){Type = 100; name=_name; attr=_attr;}
    int childNodesCount(){return 0;}
    TreeItem *child(int i)
    {return 0;}

    QString Name(){return name;}
    QString Attr(){return attr;}
private:
    QString name;
    QString attr;
};

class TreeGraphItem : public TreeItem
{
public:
    TreeGraphItem( int row, TreeModel * mod,  TreeItem *parent = 0):TreeItem(row, mod, parent){}
    ~TreeGraphItem(){}

    void setGraph(MyGraphType * _gr){Type=101;gr=_gr;}
    int childNodesCount(){return boost::num_vertices(*gr);}
    TreeItem *child(int i);

    QString Name(){return QString();}
    QString Attr(){return QString();}

private:
    MyGraphType * gr;//101
};



#endif // TREEITEM_H
