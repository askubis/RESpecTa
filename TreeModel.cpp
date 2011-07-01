
#include <QtGui>
#include <QtXml>

#include "TreeItem.h"
#include "TreeModel.h"

TreeModel::TreeModel( QObject *parent, Model * _mod, QString Name)
    : QAbstractItemModel(parent)
{
    mod=_mod;

    TreeGraphItem * grItem = new TreeGraphItem(0, this);
    graphName=Name;
    graph = mod->getGraph(Name);
    grItem->setGraph(graph);
    rootItem=grItem;
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

QGraphicsItem * TreeModel::getItemOrParent(QModelIndex index)
{
    for(TreeItem * it = (TreeItem*)index.internalPointer();;it=it->parent())
    {
        if(it->getType()==0)return ((TreeStateItem *)it)->getState();//if State then return
        if(it->getType()==1)return ((TreeTransItem *)it)->getTrans();//if Trans then return
        if(it->getType()==101)return NULL;
    }
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = (TreeItem*)(index.internalPointer());
    switch (index.column())
    {
        case 0:
        if(item)
            return item->Name();
        case 1:
        if(item)
            return item->Attr();
        default:
            return QVariant();
    }
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                              int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Attributes");
            default:
                return QVariant();
        }
    }
    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;
    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = (TreeItem*)(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    TreeItem *childItem = (TreeItem*)(child.internalPointer());
    TreeItem *parentItem = childItem->parent();
    if (!parentItem || parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    TreeItem *parentItem;
    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = (TreeItem*)(parent.internalPointer());

    return parentItem->childNodesCount();
}



