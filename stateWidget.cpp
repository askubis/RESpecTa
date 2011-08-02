 #include "stateWidget.h"
#include <QtGui>
#include <QObject>


StateWidget::StateWidget(QWidget *parent, Model * newmod )
: QWidget(parent)
{
    mod = newmod;
this->setMaximumWidth(230);
    //creating Base of the widget (background)
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

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

    StateLayout = new QVBoxLayout;

    QLabel * nameLabel = new QLabel(tr("State Name:"));
    stateNameEdit = new QLineEdit;
    connect(stateNameEdit, SIGNAL(textChanged(QString)), this, SLOT(lengthChanged(QString)));
   StateLayout->addWidget(nameLabel);
   nameLabel->setBuddy(stateNameEdit);
   StateLayout->addWidget(stateNameEdit);

    stateTypeCombo = new QComboBox(this);
    stateTypeCombo->addItems(getStateTypeTable());
    connect(stateTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setStateSubclass(int)));
   StateLayout->addWidget(stateTypeCombo);
   QLabel * paramLabel = new QLabel("Parameters:");
   paramEdit = new QLineEdit;
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
   connect(runGen, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

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
       stateNameEdit->setText("INIT");
       stateNameEdit->setDisabled(true);
   }

   mainLayout->addLayout(bottomLayout);
}

void StateWidget::lengthChanged(QString newString)
{
    if(newString.size()>0)
    {
        InsertButton->setDisabled(false);
    }
    else
    {
        InsertButton->setDisabled(true);
    }
}

void StateWidget::AcceptState()
{
    if(edited==NULL)
    {
        emit reportError(QString("Please, select a state to edit, edit it and then press OK."));
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
    OKButton->setDisabled(true);
    BaseState * tmp = edited;
    edited = NULL;
    emit ReplaceState(tmp, toInsertState);
}

void StateWidget::setStateSubclass(int chosen)
{
    if(tmpWidget==SYSTEM_INITIALIZATION)
    {
        stateNameEdit->setEnabled(true);
    }
    if(chosen==SYSTEM_INITIALIZATION)
    {
        stateNameEdit->setText("INIT");
        stateNameEdit->setDisabled(true);
    }
    StateWidgets[tmpWidget]->setVisible(false);
    tmpWidget = chosen;
    StateWidgets[tmpWidget]->setVisible(true);
}

void StateWidget::InsertState()
{
    edited = NULL;
    OKButton->setDisabled(true);
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

void StateWidget::refreshData()
{
}

void StateWidget::StateSelected(BaseState * state)
{
    if(state->getName().toLower()==QString("_end_")||state->getName().toLower()==QString("_stop_"))return;
    edited = state;
    OKButton->setDisabled(false);
    stateNameEdit->setText(state->getName());
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
    if (stateNameEdit->text().toLower()=="init" && stateTypeCombo->currentIndex()!=SYSTEM_INITIALIZATION)
    {
        emit reportError(QString("INIT name is dedicated only to SYSTEM_INITIALIZATION state"));
        return false;
    }
    if(stateNameEdit->text().toLower()=="_end_"||stateNameEdit->text().toLower()=="_stop_")
    {
        emit reportError(QString("_STOP_ and _END_ names are restricted(can be only used as ending states from the upper panel"));
        return false;
    }
    if(stateNameEdit->text().toLower().contains("<<"))
    {
        emit reportError(QString("The StateName cannot contain \"<<\""));
        return false;
    }
    if(stateNameEdit->text().toLower().contains("/"))
    {
        emit reportError(QString("The StateName cannot contain \"/\""));
        return false;
    }
    if(mod->getState(stateNameEdit->text()))
    {
        emit reportError(QString("The StateName is already in use"));
        return false;
    }
    return true;
}



