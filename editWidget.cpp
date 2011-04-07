
#include "editWidget.h"

#include <QtGui>

EditWidget::EditWidget(QWidget *parent)
    : QWidget(parent)
{

    tabWidget = new QTabWidget(this);
    tabWidget->setMaximumWidth(230);
stateWidget = new StateWidget(tabWidget);
    tabWidget->addTab(stateWidget,tr("State"));
transWidget = new TransWidget(tabWidget);
    tabWidget->addTab(transWidget, tr("Transition"));
    //tabWidget->setTabEnabled(1, false);
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(refreshWidget(int)));

    connect(stateWidget, SIGNAL(SubtaskInserted(QString)), transWidget, SLOT(SubtaskInserted(QString)));
    connect(stateWidget, SIGNAL(SubtaskInserted(QString)), (RESpecTa *)this->parentWidget(), SLOT(NewSubtaskInserted(QString)));

    connect (stateWidget, SIGNAL(InsertState(BaseState*)), (RESpecTa *)this->parentWidget(),SLOT(InsertState(BaseState*)));
    connect (stateWidget, SIGNAL(selectedSubtaskName(QString)), (RESpecTa *)this->parentWidget(),SLOT(selectedSubtaskName(QString)));





    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

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


