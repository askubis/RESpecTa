 #include "stateWidget.h"
#include <QtGui>
#include <QObject>

//#include "GraphFunctions.h"
//#include "GraphFunctions.cpp"








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
    for (std::map<std::string, MyGraphType *>::iterator it = subtasks->begin(); it!=subtasks->end() ;it++)
    {
        subtaskList<<(*it).first.c_str();
    }
    connect(subtaskCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(SubtaskIndexChanged(QString)));
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
   mainLayout->addStretch();




   sysIniWidget* sysIni = new sysIniWidget(this);
   mainLayout->addWidget(sysIni);
   tmpWidget = 0;
   StateWidgets[0]=sysIni;
   connect(sysIni, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

   runGenWidget* runGen = new runGenWidget(this);
   mainLayout->addWidget(runGen);
   runGen->setVisible(false);
   StateWidgets[1]=runGen;

   emptyGenForSetWidget* emptyForSet = new emptyGenForSetWidget(this);
   mainLayout->addWidget(emptyForSet);
   emptyForSet->setVisible(false);
   StateWidgets[2]=emptyForSet;
   connect(emptyForSet, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

   emptyGenWidget* emptyGen = new emptyGenWidget(this);
   mainLayout->addWidget(emptyGen);
   emptyGen->setVisible(false);
   StateWidgets[3]=emptyGen;

   waitStateWidget* waitGen = new waitStateWidget(this);
   mainLayout->addWidget(waitGen);
   waitGen->setVisible(false);
   StateWidgets[4]=waitGen;

   stopGenWidget* stopGen = new stopGenWidget(this);
   mainLayout->addWidget(stopGen);
   stopGen->setVisible(false);
   StateWidgets[5]=stopGen;
   connect(stopGen, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

   iniSensorWidget* initSensor = new iniSensorWidget(this);
   mainLayout->addWidget(initSensor);
   initSensor->setVisible(false);
   StateWidgets[6]=initSensor;

   getSensorWidget* getSensorReading = new getSensorWidget(this);
   mainLayout->addWidget(getSensorReading);
   getSensorReading->setVisible(false);
   StateWidgets[7]=getSensorReading;


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

void StateWidget::SubtaskIndexChanged(QString newString)
{
    emit selectedSubtaskName(newString);
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
    //RESpecTa * x = (RESpecTa *) this->parentWidget()->parentWidget()->parentWidget();
    //if(res!=x) exit(78);
    //res->insertClicked();
    BaseState * toInsertState = StateWidgets[tmpWidget]->getStateObject();
    if(toInsertState==NULL)
        return;
    toInsertState->setName(this->stateNameEdit->text().toStdString());
    toInsertState->setType(StateType(stateTypeCombo->currentIndex()));
    toInsertState->setParameters(paramEdit->text().toStdString());
    emit InsertState(toInsertState);

}

void StateWidget::createNewSubtask()
{

    if(subtaskCombo->findText(taskNameEdit->text())!=-1)
    {
        emit reportError(taskNameEdit->text().append(" is a name already\ntaken for a subtask"));
    }
    else
    {
        subtaskCombo->addItem(taskNameEdit->text());
        emit SubtaskInserted(taskNameEdit->text());
    }


}

void StateWidget::refreshData()
{

}


