
#include "editWidget.h"

#include <QtGui>

EditWidget::EditWidget(QWidget *parent, Model * newmod, Controller * newcont)
    : QWidget(parent)
{

    tabWidget = new QTabWidget(this);
    tabWidget->setMaximumWidth(230);
    tabWidget->setMinimumWidth(230);
stateWidget = new StateWidget(tabWidget, newmod, newcont);
    tabWidget->addTab(stateWidget,tr("State"));
transWidget = new TransWidget(tabWidget, newmod, newcont);
    tabWidget->addTab(transWidget, tr("Transition"));
    //tabWidget->setTabEnabled(1, false);
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(refreshWidget(int)));

    connect(stateWidget, SIGNAL(SubtaskInserted(QString)), transWidget, SLOT(SubtaskInserted(QString)));
    connect(stateWidget, SIGNAL(SubtaskInserted(QString)), (RESpecTa *)this->parentWidget(), SLOT(NewSubtaskInserted(QString)));

    connect (stateWidget, SIGNAL(InsertState(BaseState*)), (RESpecTa *)this->parentWidget(),SLOT(InsertState(BaseState*)));
    connect (stateWidget, SIGNAL(selectedSubtaskName(QString)), (RESpecTa *)this->parentWidget(),SLOT(selectedSubtaskName(QString)));

    connect (stateWidget, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

    connect (transWidget, SIGNAL(insertTransition(std::pair<QString,QString>)), (RESpecTa *)this->parentWidget(),SLOT(insertTransition(std::pair<QString,QString>)));
    //connect (transWidget, SIGNAL(getSubtasksList()), this->parentWidget(), SLOT(getSubtasksList()) );





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


