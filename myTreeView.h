class myTreeView;

#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H
#include <QtGui>
#include "respecta.h"

/**
*   Class responsible for treeview of the task.
*/
class myTreeView:public QTreeView
{
public:
    myTreeView(QWidget * parent, RESpecTa * _res):QTreeView(parent){res = _res;}
    ~myTreeView(){}
    /**
    *   A function allowing public access to selectedIndexes() from QTreeView class
    */
     //QModelIndexList getSelectedIndexes(){return selectedIndexes();}

private:
    /**
    *   A function calling main window function after selection changed.
    */
     void selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected );


     /**
     *   Signals main window to focus scene on an item, when an item is re-selected
     */
     void focusInEvent(QFocusEvent *event);

     /**
     *   Pointer to parent item.
     */
     RESpecTa * res;

};

#endif // MYTREEVIEW_H
