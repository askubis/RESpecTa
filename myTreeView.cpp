#include "myTreeView.h"

void myTreeView::selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected )
{
    res->listSelectionChanged(selectedIndexes());
    QTreeView::selectionChanged(selected, deselected);
}

void myTreeView::focusInEvent(QFocusEvent *event)
{
    if(selectedIndexes().size()!=0)
    {
        res->listSelectionChanged(selectedIndexes());
    }

    QTreeView::focusInEvent(event);
}
