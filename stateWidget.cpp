#include "stateWidget.h"
#include <QtGui>
#include <QObject>

#include "GraphFunctions.h"
#include "GraphFunctions.cpp"








StateWidget::StateWidget(QWidget *parent)
: QWidget(parent)
{
this->setMaximumWidth(230);
    //creating Base of the widget (background)
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    //mainLayout->addLayout(topLayout,1,0);



    OKButton = new QPushButton(tr("&OK"));
    OKButton->setChecked(false);
    connect(OKButton, SIGNAL(clicked()), this, SLOT(AcceptState()));
    OKButton->setDisabled(true);
    bottomLayout->addWidget(OKButton);

    InsertButton = new QPushButton(tr("&Insert"));
    InsertButton->setChecked(false);
    connect(InsertButton, SIGNAL(clicked()), this, SLOT(InsertState()));
    InsertButton->setDisabled(true);
    bottomLayout->addWidget(InsertButton);


    //creating Default EditState options
    StateLayout = new QVBoxLayout;






    QHBoxLayout *taskLayout = new QHBoxLayout;
    QLabel * taskLabel = new QLabel(tr("Task:"));
    taskNameEdit = new QLineEdit();
    createTaskButton = new QPushButton (tr("Create"));
    createTaskButton->setDisabled(true);
    connect(taskNameEdit, SIGNAL(textChanged(QString)), this, SLOT(lengthSubtaskChanged(QString)));
connect(createTaskButton, SIGNAL(clicked()), this, SLOT(createNewSubtask()));
    taskLayout->addWidget(taskLabel);
    taskLayout->addWidget(taskNameEdit);
    taskLayout->addWidget(createTaskButton);

    subtaskCombo = new QComboBox(this);
    QStringList subtaskList;
    subtaskList<<tr("MAIN");
    RESpecTa * x = (RESpecTa *) this->parentWidget()->parentWidget()->parentWidget();
    std::map<std::string, MyGraphType *> * subtasks = x->getSubtasks();
    xsubtasks = subtasks;
    for (std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end() ;it++)
    {
        subtaskList<<(*it).first.c_str();
    }

    subtaskCombo->addItems(subtaskList);
    StateLayout->addLayout(taskLayout);
    StateLayout->addWidget(subtaskCombo);

    nameLabel = new QLabel(tr("State Name:"));
    stateNameEdit = new QLineEdit;
    connect(stateNameEdit, SIGNAL(textChanged(QString)), this, SLOT(lengthChanged(QString)));
   StateLayout->addWidget(nameLabel);
   nameLabel->setBuddy(stateNameEdit);
   StateLayout->addWidget(stateNameEdit);


    stateTypeCombo = new QComboBox(this);
    stateTypeCombo->addItems(getStateTypeTable());
    connect(stateTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setStateSubclass(int)));
   StateLayout->addWidget(stateTypeCombo);
   paramLabel = new QLabel("Parameters:");
   paramEdit = new QLineEdit;
   //paramEdit->setValidator(new QDoubleValidator(-99999.0, 99999.0, 5, paramEdit));//doesn't allow multiple doubles
   StateLayout->addWidget(paramLabel);
   StateLayout->addWidget(paramEdit);






   mainLayout->addLayout(StateLayout);




   sysIni = new sysIniWidget(this);
   mainLayout->addWidget(sysIni);
   tmpWidget = 0;
   StateWidgets[0]=sysIni;


   runGen = new runGenWidget(this);
   mainLayout->addWidget(runGen);
   runGen->setVisible(false);
   StateWidgets[1]=runGen;


   emptyForSet = new emptyGenForSetWidget(this);
   mainLayout->addWidget(emptyForSet);
   emptyForSet->setVisible(false);
   StateWidgets[2]=emptyForSet;

   emptyGen = new emptyGenWidget(this);
   mainLayout->addWidget(emptyGen);
   emptyGen->setVisible(false);
   StateWidgets[3]=emptyGen;

   waitGen = new waitStateWidget(this);
   mainLayout->addWidget(waitGen);
   waitGen->setVisible(false);
   StateWidgets[4]=waitGen;

   stopGen = new stopGenWidget(this);
   mainLayout->addWidget(stopGen);
   stopGen->setVisible(false);
   StateWidgets[5]=stopGen;

   initSensor = new iniSensorWidget(this);
   mainLayout->addWidget(initSensor);
   initSensor->setVisible(false);
   StateWidgets[6]=initSensor;

   getSensorReading = new getSensorWidget(this);
   mainLayout->addWidget(getSensorReading);
   getSensorReading->setVisible(false);
   StateWidgets[7]=getSensorReading;





   //topLayout=new QVBoxLayout;
   //topLayout->addItem(StateLayout);






   mainLayout->addLayout(bottomLayout);
}

void StateWidget::lengthChanged(QString newString)
{
    if(newString.size()>0)
    {
        OKButton->setDisabled(false);
        InsertButton->setDisabled(false);
    }
    else
    {
        OKButton->setDisabled(true);
        InsertButton->setDisabled(true);
    }
}


void StateWidget::lengthSubtaskChanged(QString newString)
{
    if(newString.size()>0)
    {        createTaskButton->setDisabled(false);    }
    else
    {        createTaskButton->setDisabled(true);    }
}

void StateWidget::AcceptState()
{



}

void StateWidget::setStateSubclass(int chosen)
{
    StateWidgets[tmpWidget]->setVisible(false);
    tmpWidget = chosen;
    StateWidgets[tmpWidget]->setVisible(true);
}

void StateWidget::InsertState()
{



}

void StateWidget::createNewSubtask()
{
    std::string newSubtaskName = taskNameEdit->text().toStdString();
    RESpecTa * x = (RESpecTa *) this->parentWidget()->parentWidget()->parentWidget();
    std::map<std::string, MyGraphType *> * subtasks = x->getSubtasks();


    bool mark = false;
    for (std::map<std::string, MyGraphType *>::iterator it = xsubtasks->begin(); it!=xsubtasks->end() ;it++)
    {
//exit(7);
        if((*it).first==newSubtaskName) mark = true;

    }

    if(mark)
    {
        exit(1);
        //display error msg
        return;
    }
    else
    {
        //exit(2);
        MyGraphType * tmpGraph = new MyGraphType();
        (*xsubtasks)[newSubtaskName]= tmpGraph;
        QString newSubtask = taskNameEdit->text();
        subtaskCombo->addItem(newSubtask);

    }
    return;//*/
}
