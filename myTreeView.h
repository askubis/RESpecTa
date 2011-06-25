#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H
#include <QtGui>

class myTreeView:public QTreeView
{
public:

    myTreeView(QWidget * parent):QTreeView(parent){}
    ~myTreeView(){}
     QModelIndexList getSelectedIndexes(){return selectedIndexes();}


};

#endif // MYTREEVIEW_H
