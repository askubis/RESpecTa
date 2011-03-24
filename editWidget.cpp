
#include "editWidget.h"

#include <QtGui>

EditWidget::EditWidget(QWidget *parent)
    : QWidget(parent)
{
    tabWidget = new QTabWidget;
stateWidget = new StateWidget(this);
    tabWidget->addTab(stateWidget,tr("State"));
transWidget = new TransWidget(this);
    tabWidget->addTab(transWidget, tr("Transition"));
    //tabWidget->setTabEnabled(1, false);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

    /*







    */
}


