
#include "editWidget.h"

#include <QtGui>

EditWidget::EditWidget(QWidget *parent, Model * newmod )
    : QStackedWidget(parent)
{
    this->setMaximumWidth(230);
    //this->setMinimumWidth(230);
stateWidget = new StateWidget(this, newmod);
    this->addWidget(stateWidget);//,tr("State"));
transWidget = new TransWidget(this, newmod);
    this->addWidget(transWidget);//, tr("Transition"));
subtaskWidget = new SubtaskWidget(this, newmod);
    this->addWidget(subtaskWidget);//, tr("Subtasks"));
this->addWidget(new QWidget());

    connect(this, SIGNAL(currentChanged(int)), this, SLOT(refreshWidget(int)));

    connect(subtaskWidget, SIGNAL(added(QString)), (RESpecTa *)this->parentWidget(), SLOT(SubtaskAdded(QString)));
    connect(subtaskWidget, SIGNAL(changed(QString,QString)), (RESpecTa *)this->parentWidget(), SLOT(SubtaskChanged(QString, QString)));
    connect(subtaskWidget, SIGNAL(removed(QString)), (RESpecTa *)this->parentWidget(), SLOT(SubtaskRemoved(QString)));
    connect(subtaskWidget, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

    //connect (stateWidget, SIGNAL(InsertState(BaseState*)), (RESpecTa *)this->parentWidget(),SLOT(InsertState(BaseState*)));
    connect (stateWidget, SIGNAL(ReplaceState(BaseState * , BaseState * )), (RESpecTa *)this->parentWidget(),SLOT(ReplaceState(BaseState * , BaseState * )));
    connect (stateWidget, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

    //connect (transWidget, SIGNAL(insertTransition(std::pair<QString,QString>)), (RESpecTa *)this->parentWidget(),SLOT(insertTransition(std::pair<QString,QString>)));
    connect (transWidget, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

    connect((RESpecTa *)this->parentWidget(), SIGNAL(refreshWidgets()), this, SLOT(refreshAllWidgets()));
    connect((RESpecTa *)this->parentWidget(), SIGNAL(SignalDeleted()), this, SLOT(SignalDeleted()));
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


