class myTreeView;

#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QtGui>

/**
*   Class responsible for treeview of the task.
*/
class myTreeView:public QTreeView
{
public:
    myTreeView(QWidget * parent):QTreeView(parent){}
    ~myTreeView(){}
    /**
    *   A function allowing public access to selectedIndexes() from QTreeView class
    */
     QModelIndexList getSelectedIndexes(){return selectedIndexes();}
};

#endif // MYTREEVIEW_H
