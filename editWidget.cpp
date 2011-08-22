
#include "editWidget.h"

#include <QtGui>

EditWidget::EditWidget(RESpecTa *parent, Model * newmod )
    : QStackedWidget(parent)
{
    this->setMinimumWidth(230);
stateWidget = new StateWidget(this, newmod);
    this->addWidget(stateWidget);//,tr("State"));
transWidget = new TransWidget(this, newmod);
    this->addWidget(transWidget);//, tr("Transition"));
subtaskWidget = new SubtaskWidget(this, newmod);
    this->addWidget(subtaskWidget);//, tr("Subtasks"));
this->addWidget(new QWidget());

    connect(this, SIGNAL(currentChanged(int)), this, SLOT(refreshWidget(int)));

    connect(subtaskWidget, SIGNAL(added(QString)), parent, SLOT(SubtaskAdded(QString)));
    connect(subtaskWidget, SIGNAL(changed(QString,QString)), parent, SLOT(SubtaskChanged(QString, QString)));
    connect(subtaskWidget, SIGNAL(removed(QString)), parent, SLOT(SubtaskRemoved(QString)));
    connect(subtaskWidget, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));
    connect(subtaskWidget, SIGNAL(UncheckTasksAction()), parent, SLOT(HideTheSubtask()));

    //connect (stateWidget, SIGNAL(InsertState(BaseState*)), parent,SLOT(InsertState(BaseState*)));
    connect (stateWidget, SIGNAL(ReplaceState(BaseState * , BaseState * )), parent,SLOT(ReplaceState(BaseState * , BaseState * )));
    connect (stateWidget, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

    //connect (transWidget, SIGNAL(insertTransition(std::pair<QString,QString>)), parent,SLOT(insertTransition(std::pair<QString,QString>)));
    connect (transWidget, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

    connect(parent, SIGNAL(refreshWidgets()), this, SLOT(refreshAllWidgets()));
    connect(parent, SIGNAL(SignalDeleted()), this, SLOT(SignalDeleted()));
    this->setCurrentIndex(3);
}

void EditWidget::refreshAllWidgets()
{
    stateWidget->refreshData();
    transWidget->refreshData();
    subtaskWidget->refreshData();
}

void EditWidget::SignalDeleted()
{
    refreshWidget(this->currentIndex());

    this->setCurrentIndex(3);
    stateWidget->setOKButtonDisabled();
    transWidget->setOKButtonDisabled();
}

void EditWidget::refreshWidget(int index)
{
    switch(index)
    {
    case 0:
        stateWidget->refreshData();
        break;
    case 1:
        transWidget->refreshData();
        break;
    case 2:
        subtaskWidget->refreshData();
    default:
        break;
    }

}

void EditWidget::itemSelected(QGraphicsItem *item)
{
    if (item->type()==BaseState::Type)
    {
        this->setCurrentWidget(stateWidget);
        stateWidget->StateSelected(qgraphicsitem_cast<BaseState *>(item));
    }
    else if (item->type()==Transition::Type)
    {
        this->setCurrentWidget(transWidget);
        transWidget->TransSelected(qgraphicsitem_cast<Transition *>(item));
    }

}

void EditWidget::EditTasks()
{
    setCurrentWidget(subtaskWidget);
}


