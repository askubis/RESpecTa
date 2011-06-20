
#include "editWidget.h"

#include <QtGui>

EditWidget::EditWidget(QWidget *parent, Model * newmod )
    : QWidget(parent)
{

    tabWidget = new QTabWidget(this);
    tabWidget->setMaximumWidth(230);
    tabWidget->setMinimumWidth(230);
stateWidget = new StateWidget(tabWidget, newmod);
    tabWidget->addTab(stateWidget,tr("State"));
transWidget = new TransWidget(tabWidget, newmod);
    tabWidget->addTab(transWidget, tr("Transition"));
    //tabWidget->setTabEnabled(1, false);
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(refreshWidget(int)));



    connect (stateWidget, SIGNAL(InsertState(BaseState*)), (RESpecTa *)this->parentWidget(),SLOT(InsertState(BaseState*)));
    connect (stateWidget, SIGNAL(ReplaceState(BaseState * , BaseState * , QString)), (RESpecTa *)this->parentWidget(),SLOT(ReplaceState(BaseState * , BaseState * ,QString)));



    connect (stateWidget, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

    connect (transWidget, SIGNAL(insertTransition(std::pair<QString,QString>)), (RESpecTa *)this->parentWidget(),SLOT(insertTransition(std::pair<QString,QString>)));
    //connect (transWidget, SIGNAL(getSubtasksList()), this->parentWidget(), SLOT(getSubtasksList()) );
    connect (transWidget, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

    connect((RESpecTa *)this->parentWidget(), SIGNAL(refreshWidgets()), this, SLOT(refreshAllWidgets()));
    connect((RESpecTa *)this->parentWidget(), SIGNAL(SignalDeleted()), this, SLOT(SignalDeleted()));





    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

}

void EditWidget::refreshAllWidgets()
{
    stateWidget->refreshData();
    transWidget->refreshData();
}

void EditWidget::SignalDeleted()
{
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
    default:
        break;
    }

}

void EditWidget::itemSelected(QGraphicsItem *item)
{
    if (item->type()==BaseState::Type)
    {
        this->tabWidget->setCurrentWidget(stateWidget);
        stateWidget->StateSelected(qgraphicsitem_cast<BaseState *>(item));
    }
    else if (item->type()==Transition::Type)
    {
        this->tabWidget->setCurrentWidget(transWidget);
        transWidget->TransSelected(qgraphicsitem_cast<Transition *>(item));
    }

}


