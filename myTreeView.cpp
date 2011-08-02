#include "myTreeView.h"

void myTreeView::selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected )
{
    RESpecTa * res = (RESpecTa*)this->parent();
    res->listSelectionChanged(selected.indexes());
    //QTreeView::selectionChanged();
}
