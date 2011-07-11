class TreeModel;

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "Graph.h"
#include "Model.h"
#include "TreeItem.h"

/**
*   Class representing model of the TreeView.
*/
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel( QObject *parent, Model * mod, QString Name);
    ~TreeModel();

    /**
    *   Returns data (text) from the index.
    */
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    /**
    *   Returns data for headers of the view.
    */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    /**
    *   Returns index fromt he current row and column.
    */
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    /**
    *   Returns parent of the given item.
    *   @param child Item, of which the parent is needed.
    */
    QModelIndex parent(const QModelIndex &child) const;
    /**
    *   Returns number of childitems of the current item.
    */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
    *   Returns number of colums in the view.
    */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    /**
    *   Returns graphics item of the item at the given index, or of it's parent (recursively).
    */
    QGraphicsItem * getItemOrParent( QModelIndex index);
    /**
    *   Model of the project.
    */
    Model * mod;
private:
    /**
    *   Name of the graph, which is represented.
    */
    QString graphName;
    /**
    *   Root item of the view.
    */
    TreeItem *rootItem;
};

#endif // TREEMODEL_H
