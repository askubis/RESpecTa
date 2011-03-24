#include "stateWidget.h"
#include <QtGui>
#include <QObject>



StateWidget::StateWidget(QWidget *parent)
: QWidget(parent)
{

    //creating Base of the widget (background)
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    QGridLayout *mainLayout = new QGridLayout;
    setLayout(mainLayout);
    //mainLayout->addLayout(topLayout,1,0);

    mainLayout->addLayout(bottomLayout,3,0);

    OKButton = new QPushButton(tr("&OK"));
    OKButton->setChecked(false);
    connect(OKButton, SIGNAL(clicked()), this, SLOT(AcceptState()));
    bottomLayout->addWidget(OKButton);

    InsertButton = new QPushButton(tr("&Insert"));
    InsertButton->setChecked(false);
    connect(InsertButton, SIGNAL(clicked()), this, SLOT(InsertState()));
    bottomLayout->addWidget(InsertButton);


    //creating Default EditState options
    StateLayout = new QVBoxLayout;
//subtask checkbox, subtask combobox, subtask nameEdit, subtask Create button
//argument floatEdit, string ParamEdit
    nameLabel = new QLabel(tr("State Name:"));
    stateNameEdit = new QLineEdit;
    //nameLabel->setBuddy(stateNameEdit);
    connect(stateNameEdit, SIGNAL(textChanged(QString)), this, SLOT(lengthChanged(QString)));
   StateLayout->addWidget(nameLabel);
   StateLayout->addWidget(stateNameEdit);
    QStringList items;
    items << tr("SYSTEM_INITIALIZATION") << tr("RUN_GENERATOR") << tr("EMPTY_GEN_FOR_SET") << tr("EMPTY_GEN") << tr("WAIT") <<
            tr("STOP_GEN") << tr("CUBE_STATE_INIT") << tr("INITIATE_SENSOR_READING") << tr("GET_SENSOR_READING") <<
            tr("CUBE_STATE_WRITING") << tr("CUBE_STATE_CHANGE") << tr("COMMUNICATE_WITH_SOLVER") <<
            tr("MANIPULATION_SEQ_TRANSLATION");
    genTypeCombo = new QComboBox(this);
    genTypeCombo->addItems(items);
    connect(genTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setStateSubclass(int)));
   StateLayout->addWidget(genTypeCombo);

   topLayout=new QVBoxLayout;
   topLayout->addItem(StateLayout);
   mainLayout->addLayout(topLayout,1,0);




}

void StateWidget::lengthChanged(QString newString)
{
    if(newString.size()>0)
    {
        OKButton->setDown(false);
    }
    else
    {
        OKButton->setDown(true);
    }
}

void StateWidget::AcceptState()
{
    //exit(1);

    //this->repaint();
    //mainLayout->addLayout->

    //mainLayout->addLayout(topLayout,1,0);
}

void StateWidget::setStateSubclass(int chosen)
{

    switch(chosen)
    {
    case SYSTEM_INITIALIZATION:

        break;
    default:

        break;
    }

}

void StateWidget::InsertState()
{


}
