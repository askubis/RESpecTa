
#include <QtXml>

#include "TreeItem.h"


TreeItem::TreeItem( int row, TreeItem *parent)
{
    Type = 255;

    rowNumber = row;
    parentItem = parent;
}

TreeItem::~TreeItem()
{
    QHash<int,TreeItem*>::iterator it;
    for (it = childItems.begin(); it != childItems.end(); ++it)
        delete it.value();
}

TreeItem *TreeItem::parent()
{
    return parentItem;
}

int TreeItem::row()
{
    return rowNumber;
}

TreeItem * TreeStateItem::child(int i)
{
    if (childItems.contains(i))
        return childItems[i];
    TreeItem * tmp = state->getChild(i, this);
    childItems[i]=tmp;
    return tmp;
}

TreeItem * TreeTransItem::child(int i)
{
    if (childItems.contains(i))
        return childItems[i];
    if(tr->getSubtask().size()>0)
    {
        TreeTextItem * tmp = new TreeTextItem(i, this);
        tmp->setNameAttr("Subtask", tr->getSubtask());
        childItems[i]=tmp;
        return tmp;
    }
    return 0;
}

TreeItem * TreeCoordItem::child(int i)
{
    if (childItems.contains(i))
        return childItems[i];
    int index = i;
    if(isProper(coords->getMotionType()))
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, this);
            tmp->setNameAttr("MotionType", QString().fromStdString(MOTION_TYPE_TABLE[coords->getMotionType()]));
            childItems[i]=tmp;
            return tmp;
        }
        else
        {
            index--;
        }
    }
    if(isProper(coords->getCoordType()))
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, this);
            tmp->setNameAttr("CoordType", QString().fromStdString(COORD_TYPE_TABLE[coords->getCoordType()]));
            childItems[i]=tmp;
            return tmp;
        }
        else
        {
             index--;
        }
    }
    foreach(Pose * pos, coords->getPoses())
    {
        if(index==0)
        {
            TreePoseItem * tmp = new TreePoseItem(i, this);
            tmp->setPos(pos);
            childItems[i]=tmp;
            return tmp;
        }
        else
        {
            index--;
        }
    }
    return 0;
}

TreeItem * TreeRobotSetItem::child(int i)
{
    int index=i;
    if (childItems.contains(i))
        return childItems[i];
    foreach(Robot rob, set)
    {
        if(index==0)
        {
            TreeTextItem * tmp = new TreeTextItem(i, this);
            tmp->setNameAttr("Robot", QString().fromStdString(ROBOT_TABLE[rob]));
            childItems[i]=tmp;
            return tmp;
        }
        else
        {
            index--;
        }
    }
    return 0;
}

TreeItem * TreeInitItem::child(int i)
{
    if (childItems.contains(i))
        return childItems[i];
    int index = i;
    for(int j=0;j<init.init_values.size();j++)
    {
        if(index==0)
        {
            std::pair<GeneratorType, int> myPair=init.init_values[j];
            TreeTextItem * tmp = new TreeTextItem(i, this);
            char table[10];
            sprintf(table,"%d", myPair.second);
            tmp->setNameAttr(QString().fromStdString(GENERATOR_TYPE_TABLE[myPair.first]), table);
            childItems[i]=tmp;
            return tmp;
        }
        else
        {
            index--;
        }
    }
    return 0;
}

TreeItem *TreePoseItem::child(int i)
{
    if (childItems.contains(i))
        return childItems[i];
    std::vector<double> a;
    QString tmpName;
    if(i==0)
    {
        a = pos->getA();
        tmpName = "Accelerations";
    }
    else if(i==1)
    {
        a = pos->getV();
        tmpName = "Velocities";
    }
    else if(i==2)
    {
        a = pos->getC();
        tmpName = "Coordinates";
    }
    else
    {
        return 0;
    }
    QString value;
    TreeTextItem * tmp = new TreeTextItem(i, this);
    for(int j = 0;j<a.size();j++)
    {
        char table[10];
        sprintf(table,"%d ", a[j]);
        value.append(table);
    }
    tmp->setNameAttr(tmpName, value);
    childItems[i]=tmp;
    return tmp;
}

TreeItem * TreeGraphItem::child(int i)
{
    if (childItems.contains(i))
        return childItems[i];

    TreeStateItem * tmp = new TreeStateItem(i, this);
    childItems[i]=tmp;
    tmp->setState(Model->mod->getState(gr, i));
    return tmp;
}


