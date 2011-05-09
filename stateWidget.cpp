 #include "stateWidget.h"
#include <QtGui>
#include <QObject>

//#include "GraphFunctions.h"
//#include "GraphFunctions.cpp"








StateWidget::StateWidget(QWidget *parent, Model * newmod )
: QWidget(parent)
{
    mod = newmod;
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
    connect(subtaskCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(SubtaskIndexChanged(QString)));
    subtaskCombo->addItems(mod->getTasksNameLists());
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




   sysIniWidget* sysIni = new sysIniWidget(this, mod  );
   mainLayout->addWidget(sysIni);
   tmpWidget = 0;
   StateWidgets[0]=sysIni;
   connect(sysIni, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

   runGenWidget* runGen = new runGenWidget(this,  mod  );
   mainLayout->addWidget(runGen);
   runGen->setVisible(false);
   StateWidgets[1]=runGen;

   emptyGenForSetWidget* emptyForSet = new emptyGenForSetWidget(this,  mod  );
   mainLayout->addWidget(emptyForSet);
   emptyForSet->setVisible(false);
   StateWidgets[2]=emptyForSet;
   connect(emptyForSet, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

   emptyGenWidget* emptyGen = new emptyGenWidget(this,  mod  );
   mainLayout->addWidget(emptyGen);
   emptyGen->setVisible(false);
   StateWidgets[3]=emptyGen;

   waitStateWidget* waitGen = new waitStateWidget(this,  mod  );
   mainLayout->addWidget(waitGen);
   waitGen->setVisible(false);
   StateWidgets[4]=waitGen;

   stopGenWidget* stopGen = new stopGenWidget(this,  mod  );
   mainLayout->addWidget(stopGen);
   stopGen->setVisible(false);
   StateWidgets[5]=stopGen;
   connect(stopGen, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

   iniSensorWidget* initSensor = new iniSensorWidget(this,  mod  );
   mainLayout->addWidget(initSensor);
   initSensor->setVisible(false);
   StateWidgets[6]=initSensor;

   getSensorWidget* getSensorReading = new getSensorWidget(this,  mod  );
   mainLayout->addWidget(getSensorReading);
   getSensorReading->setVisible(false);
   StateWidgets[7]=getSensorReading;

   if(tmpWidget==SYSTEM_INITIALIZATION)
   {
       stateNameEdit->setText("_INIT_");
       stateNameEdit->setDisabled(true);
   }

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
    if(edited==NULL)
    {
        emit reportError(QString().fromStdString("Please, select a state to edit, edit it and then press OK."));
        return;
    }
    if ( !StateNameOK())
    {
        return;
    }
    BaseState * toInsertState = StateWidgets[tmpWidget]->getStateObject();
    if(toInsertState==NULL)
        return;
    toInsertState->setName(this->stateNameEdit->text());
    toInsertState->setType(StateType(stateTypeCombo->currentIndex()));
    toInsertState->setParameters(paramEdit->text());
    //create some signal to send it, needs to be stated which state is changed
    emit ReplaceState(edited, toInsertState);
    edited = NULL;
}

void StateWidget::setStateSubclass(int chosen)
{
    if(tmpWidget==SYSTEM_INITIALIZATION)
    {
        stateNameEdit->setEnabled(true);
    }
    if(chosen==SYSTEM_INITIALIZATION)
    {
        stateNameEdit->setText("_INIT_");
        stateNameEdit->setDisabled(true);
    }
    StateWidgets[tmpWidget]->setVisible(false);
    tmpWidget = chosen;
    StateWidgets[tmpWidget]->setVisible(true);

}

void StateWidget::InsertState()
{
    edited = NULL;
    if ( !StateNameOK())
    {
        return;
    }
    BaseState * toInsertState = StateWidgets[tmpWidget]->getStateObject();
    if(toInsertState==NULL)
        return;
    toInsertState->setName(this->stateNameEdit->text());
    toInsertState->setType(StateType(stateTypeCombo->currentIndex()));
    toInsertState->setParameters(paramEdit->text());
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
    subtaskCombo->clear();
    subtaskCombo->addItems(mod->getTasksNameLists());
}

void StateWidget::StateSelected(BaseState * state)
{
    edited = state;
    stateNameEdit->setText(state->getName());
    subtaskCombo->setCurrentIndex(subtaskCombo->findText(QString().fromStdString(mod->getSubtaskName(QString(state->getName())))));
    paramEdit->setText(state->getParameters());
    stateTypeCombo->setCurrentIndex(state->getType());
    StateWidgets[tmpWidget]->setVisible(false);
    if(state->getType()<STATE_TYPES_NUMBER)
    {
        tmpWidget = state->getType();
        StateWidgets[tmpWidget]->setVisible(true);
        StateWidgets[tmpWidget]->setState(state);
    }

}

bool StateWidget::StateNameOK()
{
    if (stateNameEdit->text()=="_INIT_" && stateTypeCombo->currentIndex()!=SYSTEM_INITIALIZATION)
    {
        emit reportError(QString().fromStdString("_INIT_ name is dedicated only to SYSTEM_INITIALIZATION state"));
        return false;
    }
    if(stateNameEdit->text()=="_END_"||stateNameEdit->text()=="_end_"||stateNameEdit->text()=="_stop_"||stateNameEdit->text()=="_STOP_")
    {
        emit reportError(QString().fromStdString("_STOP_ and _END_ names are restricted(can be only used\nas ending states from the upper panel"));
        return false;
    }
    return true;
}



