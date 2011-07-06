class TreeModel;

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "Graph.h"
#include "Model.h"
#include "TreeItem.h"

//class TreeItem;
//class TreeStateItem;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel( QObject *parent, Model * mod, QString Name);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QGraphicsItem * getItemOrParent( QModelIndex index);

    QString graphName;
    Model * mod;
private:
    MyGraphType * graph;
    TreeItem *rootItem;
};

#endif // TREEMODEL_H
