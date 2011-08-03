#include "myTreeView.h"

void myTreeView::selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected )
{
    res->listSelectionChanged(selectedIndexes());
    QTreeView::selectionChanged(selected, deselected);
}
