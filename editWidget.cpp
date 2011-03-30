
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
//    connect(tabWidget, SIGNAL(currentChanged(int)), )

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

    /*







    */
}


