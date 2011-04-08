#include "StateTypeWidgets.h"
#include <QtGui>

//dal kazdego umiescic w nim jego Typ Stanu i zrobic funkcje Get oraz Set


//***************   SYS_INITIALIZATION   ***************//

sysIniWidget::sysIniWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * sysIniLayout = new QVBoxLayout;

    robotsInitialized = new QListWidget;
    sysIniLayout->addWidget(robotsInitialized);
    QPushButton * removeRobotButton = new QPushButton("Remove Selected");
    sysIniLayout->addWidget(removeRobotButton);
    connect (removeRobotButton, SIGNAL(clicked()), this, SLOT(removeECPSection()));
    QPushButton * iniAddRobotButton = new QPushButton ("Create ECP section");
    connect (iniAddRobotButton, SIGNAL(clicked()), this, SLOT(createECPSection()));
    sysIniLayout->addWidget(iniAddRobotButton);

    QPushButton * iniAddMPButton = new QPushButton ("Change MP section");
    connect (iniAddMPButton, SIGNAL(clicked()), this, SLOT(changeMPSection()));
    sysIniLayout->addWidget(iniAddMPButton);

    this->setLayout(sysIniLayout);
    ecpDialog = new ECPDialog(this);
    ecpDialog->setVisible(false);
    mpDialog = new MPDialog(this);
    mpDialog->setVisible(false);

    State = new sysInitState();
    State->setTransmitter(Transmitter(TRANSMITTERS_NUMBER));

    connect(ecpDialog, SIGNAL(InsertECP(genInit)), this, SLOT(InsertECP(genInit)));
    connect(mpDialog, SIGNAL(InsertMP(std::vector<Sensor>,Transmitter)), this, SLOT(InsertMP(std::vector<Sensor>,Transmitter)));
}

void sysIniWidget::InsertMP (std::vector<Sensor> sensors, Transmitter trans)
{
    this->State->setSensors(sensors);
    this->State->setTransmitter(trans);
}

void sysIniWidget::InsertECP(genInit newInit)
{
    std::vector<genInit> inits = this->State->getInits();
    for (std::vector<genInit>::iterator it = inits.begin();it!=inits.end();it++)
    {
        if((*it).robot == newInit.robot)
        {
            //display exists
            return;
        }
    }
    inits.push_back(newInit);
    this->State->setInits(inits);
    this->robotsInitialized->addItem(QString().fromStdString(ROBOT_TABLE[newInit.robot]));
}

void sysIniWidget::removeECPSection()
{
    QList<QListWidgetItem *> toDeleteItems = robotsInitialized->selectedItems();
    std::vector<genInit> genIniVector;
    genIniVector = this->State->getInits();
    int size = toDeleteItems.size();
    std::vector<genInit>::iterator tmp_it;
    for (int i=0;i<size;i++)
    {
        for(std::vector<genInit>::iterator it=genIniVector.begin(); it!=genIniVector.end(); )
        {
            tmp_it=it;
            tmp_it++;
            if(toDeleteItems[i]->text().toStdString()==ROBOT_TABLE[(*it).robot])
            {
                genIniVector.erase(it);
                break;
            }
            it=tmp_it;
        }
        delete toDeleteItems[i];
    }
    this->State->setInits(genIniVector);

}
void sysIniWidget::createECPSection()
{
    //ecpDialog->exec();
    ecpDialog->setVisible(true);
}
void sysIniWidget::changeMPSection()
{
    mpDialog->exec();
    //mpDialog->setVisible(true);
    //show edit dialog with things included in the MP section
}

BaseState * sysIniWidget::getStateObject()
{
    return new sysInitState(*State);
}



//***************   RUN_GENERATOR   ***************//

runGenWidget::runGenWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * runGenLayout = new QVBoxLayout;
    robotCombo = new QComboBox(this);
    robotCombo->addItems(getRobotTable());
    runGenLayout->addWidget(robotCombo);
    genTypeCombo = new QComboBox(this);
    genTypeCombo->setFixedWidth(200);
    genTypeCombo->addItems(getGeneratorTypeTable());
    runGenLayout->addWidget(genTypeCombo);
    //connect(stateTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setStateSubclass(int)));
    argsLabel = new QLabel("Arguments:");
    argsLineEdit = new QLineEdit;
    //argsLineEdit->setValidator(new QDoubleValidator(-99999.0, 99999.0, 5, argsLineEdit));//doesn't allow multiple doubles
    runGenLayout->addWidget(argsLabel);
    runGenLayout->addWidget(argsLineEdit);
    speechLabel = new QLabel("Speech:");
    speechLineEdit = new QLineEdit;
    runGenLayout->addWidget(speechLabel);
    runGenLayout->addWidget(speechLineEdit);



    QHBoxLayout *filePathLayout = new QHBoxLayout();
    QLabel * filePathLabel = new QLabel ("Path to .trj file:");
    filePathLayout->addWidget(filePathLabel);
    QPushButton * setFilePathButton = new QPushButton("...");
    filePathLayout->addWidget(setFilePathButton);
    runGenLayout->addLayout(filePathLayout);
    connect(setFilePathButton, SIGNAL(clicked()), this, SLOT(selectTrjFilePath()));
    trjFileName=new QLineEdit();
    runGenLayout->addWidget(trjFileName);

    QPushButton * runGenAddPoseButton = new QPushButton (tr("Edit Poses"));
    connect(runGenAddPoseButton, SIGNAL(clicked()), this, SLOT(showAddPosesDialog()));
    runGenLayout->addWidget(runGenAddPoseButton);
    setLayout(runGenLayout);

    poseDialog = new PoseDialog(this);
    poseDialog->setVisible(false);

    State = new RunGenState();

    connect(poseDialog, SIGNAL(InsertCoords(Coordinates*)), this, SLOT(CoordsInsert(Coordinates*)));

}

void runGenWidget::CoordsInsert(Coordinates * newCoords)
{
    Coordinates * toDelete = this->State->getCoords();
    delete toDelete;
    this->State->setCoords(newCoords);
}

void runGenWidget::selectTrjFilePath()
{
    QFileDialog::Options options;
    //if (!native->isChecked())
      //  options |= QFileDialog::DontUseNativeDialog;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("QFileDialog::getOpenFileName()"),
                                trjFileName->text(),
                                tr("Trajectory Files(*.trj);;All Files (*)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
        trjFileName->setText(fileName);
}

void runGenWidget::showAddPosesDialog()
{
    //poseDialog->setVisible(true);
    poseDialog->exec();
}

BaseState * runGenWidget::getStateObject()
{
    Coordinates * tmp = State->getCoords();
    State->setArgs(argsLineEdit->text().toStdString());
    State->setSpeech(speechLineEdit->text().toStdString());
    State->setGenType(GeneratorType(genTypeCombo->currentIndex()));
    tmp->setFilePath(trjFileName->text().toStdString());
    State->setCoords(tmp);
    return new RunGenState(*State);
}


//***************   EMPTY_GEN_FOR_SET   ***************//


emptyGenForSetWidget::emptyGenForSetWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * emptyGenLayout = new QVBoxLayout;

    QLabel *FirstSetLabel = new QLabel(tr("First Set:"));
    emptyGenLayout->insertWidget(0,FirstSetLabel);

    FirstRobotList = new QListWidget(this);
    emptyGenLayout->insertWidget(1,FirstRobotList);

    FirstRobotCombo = new QComboBox(this);
    FirstRobotCombo->setFixedWidth(200);
    FirstRobotCombo->addItems(getRobotTable());
    emptyGenLayout->insertWidget(2,FirstRobotCombo);

    QHBoxLayout * firstButtonsLayout = new QHBoxLayout;
    QPushButton * addFirstButton = new QPushButton("Add");
    connect(addFirstButton, SIGNAL(clicked()), this, SLOT(addFirst()));
    QPushButton * removeFirstButton = new QPushButton("Remove");
    connect(removeFirstButton, SIGNAL(clicked()), this, SLOT(removeFirst()));
    firstButtonsLayout->addWidget(addFirstButton);
    firstButtonsLayout->addWidget(removeFirstButton);
    emptyGenLayout->insertLayout(3,firstButtonsLayout);

    QLabel *SecondSetLabel = new QLabel("Second Set:");
    emptyGenLayout->insertWidget(4,SecondSetLabel);

    SecondRobotList = new QListWidget(this);
    emptyGenLayout->insertWidget(5,SecondRobotList);

    SecondRobotCombo = new QComboBox(this);
    SecondRobotCombo->setFixedWidth(200);
    SecondRobotCombo->addItems(getRobotTable());
    emptyGenLayout->insertWidget(6,SecondRobotCombo);

    QHBoxLayout * secondButtonsLayout = new QHBoxLayout;
    QPushButton * addSecondButton = new QPushButton("Add");
    connect(addSecondButton, SIGNAL(clicked()), this, SLOT(addSecond()));
    QPushButton * removeSecondButton = new QPushButton("Remove");
    connect(removeSecondButton, SIGNAL(clicked()), this, SLOT(removeSecond()));
    secondButtonsLayout->addWidget(addSecondButton);
    secondButtonsLayout->addWidget(removeSecondButton);
    emptyGenLayout->insertLayout(7,secondButtonsLayout);

     setLayout(emptyGenLayout);

     State = new EmptyGenForSetState();
}

void emptyGenForSetWidget::addFirst()
{
    if (FirstRobotList->findItems(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {        /*display present*/    }
    else
    {        FirstRobotList->addItem(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]));    }
}

void emptyGenForSetWidget::removeFirst()
{
    if (FirstRobotList->findItems(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {        delete (FirstRobotList->findItems(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]), Qt::MatchFlags()))[0];    }
    else
    {        /*display not present*/    }
}

void emptyGenForSetWidget::addSecond()
{
    if (SecondRobotList->findItems(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {        /*display present*/    }
    else
    {        SecondRobotList->addItem(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()]));    }
}

void emptyGenForSetWidget::removeSecond()
{
    if (SecondRobotList->findItems(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {        delete (SecondRobotList->findItems(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()]), Qt::MatchFlags()))[0];    }
    else
    {        /*display not present*/    }
}

BaseState * emptyGenForSetWidget::getStateObject()
{
    RobotSet tmp;
    tmp = this->State->getSet();
    tmp.first.clear();
    tmp.second.clear();
    for (int i=0;i<ROBOTS_NUMBER;i++)
    {
        if (FirstRobotList->findItems(QString().fromStdString(ROBOT_TABLE[i]), Qt::MatchFlags()).size())
        {
            tmp.first.push_back(Robot(i));
        }
        if (SecondRobotList->findItems(QString().fromStdString(ROBOT_TABLE[i]), Qt::MatchFlags()).size())
        {
            tmp.second.push_back(Robot(i));
        }
    }
    this->State->setSet(tmp);
    return new EmptyGenForSetState(*State);
}

//***************   EMPTY_GEN   ***************//

emptyGenWidget::emptyGenWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * emptyGenLayout = new QVBoxLayout;

    QLabel *SetLabel = new QLabel(tr("Robot:"));
    emptyGenLayout->addWidget(SetLabel);

    RobotCombo = new QComboBox(this);
    RobotCombo->setFixedWidth(200);
    RobotCombo->addItems(getRobotTable());
    emptyGenLayout->addWidget(RobotCombo);

    setLayout(emptyGenLayout);

    State = new EmptyGenState();
}

BaseState * emptyGenWidget::getStateObject()
{
    this->State->setRobot(Robot(RobotCombo->currentIndex()));
    return new EmptyGenState(*State);
}

//***************   WAIT_GEN   ***************//

waitStateWidget::waitStateWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * waitLayout = new QVBoxLayout;

    QLabel *TimeLabel = new QLabel(tr("TimeSpan"));
    timeSpan = new QLineEdit;
    timeSpan->setValidator(new QIntValidator(timeSpan));
    waitLayout->addWidget(TimeLabel);
    waitLayout->addWidget(timeSpan);

    setLayout(waitLayout);
    State = new WaitState();
}

BaseState * waitStateWidget::getStateObject()
{
    this->State->setTimespan(timeSpan->text().toLongLong());
    return new WaitState(*State);
}

//***************   STOP_GEN   ***************//

stopGenWidget::stopGenWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * stopGenLayout = new QVBoxLayout;

    QLabel *SetLabel = new QLabel(tr("First Set:"));
    stopGenLayout->insertWidget(0,SetLabel);

    RobotList = new QListWidget(this);
    stopGenLayout->insertWidget(1,RobotList);

    RobotCombo = new QComboBox(this);
    RobotCombo->setFixedWidth(200);
    RobotCombo->addItems(getRobotTable());
    stopGenLayout->insertWidget(2,RobotCombo);

    QHBoxLayout * buttonsLayout = new QHBoxLayout;
    QPushButton * addButton = new QPushButton("Add");
    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    QPushButton * removeButton = new QPushButton("Remove");
    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    stopGenLayout->insertLayout(3,buttonsLayout);

     setLayout(stopGenLayout);

     State = new StopGenState();
}

void stopGenWidget::add()
{
    if (RobotList->findItems(QString().fromStdString(ROBOT_TABLE[RobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {        /*DISPLAY info "present"*/    }
    else
    {        RobotList->addItem(QString().fromStdString(ROBOT_TABLE[RobotCombo->currentIndex()]));    }
}

void stopGenWidget::remove()
{
    if (RobotList->findItems(QString().fromStdString(ROBOT_TABLE[RobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {        delete (RobotList->findItems(QString().fromStdString(ROBOT_TABLE[RobotCombo->currentIndex()]), Qt::MatchFlags()))[0];    }
    else
    {        /*DISPLAY info "not present"*/    }
}

BaseState * stopGenWidget::getStateObject()
{
    RobotSet tmp;
    tmp = this->State->getSet();
    tmp.first.clear();
    for (int i=0;i<ROBOTS_NUMBER;i++)
    {
        if (RobotList->findItems(QString().fromStdString(ROBOT_TABLE[i]), Qt::MatchFlags()).size())
        {
            tmp.first.push_back(Robot(i));
        }
    }
    this->State->setSet(tmp);
    return new StopGenState(*State);
}

//***************   SENSOR_INI_GEN   ***************//

iniSensorWidget::iniSensorWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * iniSensorLayout = new QVBoxLayout;

    QLabel *sensorLabel = new QLabel(tr("Sensor:"));
    iniSensorLayout->addWidget(sensorLabel);

    SensorCombo = new QComboBox(this);
    SensorCombo->setFixedWidth(200);
    SensorCombo->addItems(getSensorTable());
    iniSensorLayout->addWidget(SensorCombo);

    setLayout(iniSensorLayout);

    State = new InitiateSensorState();
}

BaseState * iniSensorWidget::getStateObject()
{
    this->State->setSensor(Sensor(SensorCombo->currentIndex()));
    return new InitiateSensorState(*State);
}

//***************   GET_SENSOR_GEN   ***************//

getSensorWidget::getSensorWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * getSensorLayout = new QVBoxLayout;

    QLabel *sensorLabel = new QLabel(tr("Sensor:"));
    getSensorLayout->addWidget(sensorLabel);

    SensorCombo = new QComboBox(this);
    SensorCombo->setFixedWidth(200);
    SensorCombo->addItems(getSensorTable());
    getSensorLayout->addWidget(SensorCombo);

    setLayout(getSensorLayout);

    State = new GetSensorState();
}

BaseState * getSensorWidget::getStateObject()
{
    this->State->setSensor(Sensor(SensorCombo->currentIndex()));
    return new GetSensorState(*State);
}



//***********************************************   DIALOGS   ***********************************************//




//***************   POSE_DIALOG   ***************//

PoseDialog::PoseDialog(QWidget * parent): QDialog(parent)
{
    setWindowTitle(tr("Pose"));
    QGridLayout * mainLayout = new QGridLayout;

    QLabel * CoordTypeLabel = new QLabel("Pose specification:");
    mainLayout->addWidget(CoordTypeLabel,0,0,1,2);
    coordTypeCombo = new QComboBox;
    coordTypeCombo->addItems(getCoordTypeTable());
    mainLayout->addWidget(coordTypeCombo, 1,0,1,2);
    QLabel * MotionTypeLabel = new QLabel("Motion type:");
    mainLayout->addWidget(MotionTypeLabel,2,0,1,2);
    motionTypeCombo = new QComboBox;
    motionTypeCombo->addItems(getMotionTypeTable());
    mainLayout->addWidget(motionTypeCombo,3,0,1,2);

    poseList = new QListWidget();
    mainLayout->addWidget(poseList, 4, 0, 3, 2);

    QPushButton * addPoseButt = new QPushButton("Add");
    mainLayout->addWidget(addPoseButt, 7, 0);
    connect(addPoseButt, SIGNAL(clicked()), this, SLOT(AddPose()) );

    /*QPushButton * rmPoseButt = new QPushButton("Remove");
    mainLayout->addWidget(rmPoseButt,7,1);
    connect(addPoseButt, SIGNAL(clicked()), this, SLOT(RemovePose()) );*/

    QLabel * coordLabel = new QLabel("Coordinates");
    mainLayout->addWidget(coordLabel, 0, 2);
    QLabel * velocityLabel = new QLabel("Velocities");
    mainLayout->addWidget(velocityLabel, 0, 3);
    QLabel * accelerationLabel = new QLabel("Accelerations");
    mainLayout->addWidget(accelerationLabel, 0, 4);

    for (int i = 0;i<7;i++)
    {
        coordEdit.push_back(new QLineEdit(this));
        coordEdit[i]->setValidator(new QDoubleValidator(-99999.0,99999.0, 5,coordEdit[i]));
        coordEdit[i]->setMaximumWidth(80);
        mainLayout->addWidget(coordEdit[i], i+1, 2);

        velEdit.push_back(new QLineEdit(this));
        velEdit[i]->setValidator(new QDoubleValidator(-99999.0,99999.0, 5,velEdit[i]));
        velEdit[i]->setMaximumWidth(80);
        mainLayout->addWidget(velEdit[i], i+1, 3);

        accEdit.push_back(new QLineEdit(this));
        accEdit[i]->setValidator(new QDoubleValidator(-99999.0,99999.0, 5,accEdit[i]));
        accEdit[i]->setMaximumWidth(80);
        mainLayout->addWidget(accEdit[i], i+1, 4);
    }

    QPushButton * resetAllButton = new QPushButton ("Reset all poses");
    connect(resetAllButton, SIGNAL(clicked()), this, SLOT(PosesReset()) );
    mainLayout->addWidget(resetAllButton, 8, 0, 1, 2);

    QPushButton * cancelButton = new QPushButton ("Cancel");
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(PoseCancel()) );
    mainLayout->addWidget(cancelButton, 8, 2);

    QPushButton * addButton = new QPushButton ("OK");
    connect(addButton, SIGNAL(clicked()), this, SLOT(PoseOK()) );
    mainLayout->addWidget(addButton, 8, 3, 1, 2);
    connect(this, SIGNAL(rejected()), this, SLOT(PoseCancel()) );

    coords = new Coordinates();

    this->setLayout(mainLayout);
}

void PoseDialog::AddPose()
{
    Pose * tmp = new Pose();
    std::vector<int> a, v, c;
    int i = 0;
    for (;i<7;i++)
    {
        if(coordEdit[i]->text().isEmpty() || velEdit[i]->text().isEmpty() || accEdit[i]->text().isEmpty())
        {
            break;
        }
        else
        {
            a.push_back(accEdit[i]->text().toInt());
            v.push_back(velEdit[i]->text().toInt());
            c.push_back(coordEdit[i]->text().toInt());
        }
    }
    if(i!=0)
    {
        tmp->setA(a);
        tmp->setV(v);
        tmp->setC(c);
        std::vector<Pose *> pos_vec= coords->getPoses();
        pos_vec.push_back(tmp);
        coords->setPoses(pos_vec);
        poseList->addItem(QString().fromStdString("kopytko"));
    }
}

void PoseDialog::RemovePose()
{/*
    QList<QListWidgetItem *> toDeleteItems = poseList->selectedItems();
    for (int i=0;i<toDeleteItems.size();i++)
    {
        poseList->find(toDeleteItems[i]);
    }
    for (int i = 0; i<poseList->sel; i++)
    {
        ;
    }

    //*/
}

void PoseDialog::PoseOK()
{
    coords->setCoordType(CoordType(coordTypeCombo->currentIndex()));
    coords->setMotionType(MotionType(motionTypeCombo->currentIndex()));
    emit InsertCoords(new Coordinates(*coords));
    this->setVisible(false);
}

void PoseDialog::PoseCancel()
{
    this->setVisible(false);
}

void PoseDialog::PosesReset()
{
    poseList->clear();
    delete coords;
    coords = new Coordinates();

}

//***************   ECP_DIALOG   ***************//
ECPDialog::ECPDialog(QWidget * parent): QDialog(parent)
{
    setWindowTitle(tr("ECPDialog"));
    QGridLayout * mainLayout = new QGridLayout;

    robotCombo = new QComboBox;
    robotCombo->addItems(getRobotTable());
    mainLayout->addWidget(robotCombo, 0,0,1,3);

    genTypeCombo = new QComboBox;
    genTypeCombo->addItems(getGeneratorTypeTable());
    mainLayout->addWidget(genTypeCombo,1,0,1,3);
    QLabel * argLabel = new QLabel("Init argument:");
    mainLayout->addWidget(argLabel, 2,0,1,3);
    argLineEdit = new QLineEdit();
    argLineEdit->setValidator(new QIntValidator(argLineEdit));
    mainLayout->addWidget(argLineEdit,3,0,1,3);

    QPushButton * addButton = new QPushButton("Add");
    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    QPushButton * removeButton = new QPushButton("Remove selected");
    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    mainLayout->addWidget(addButton,4,0);
    mainLayout->addWidget(removeButton,4,1, 1, 2);

    genList = new QListWidget();
    mainLayout->addWidget(genList,5, 0, 3, 3);

    QPushButton *OKButton = new QPushButton("OK");
    connect (OKButton, SIGNAL(clicked()), this, SLOT(OKPressed()));
    mainLayout->addWidget(OKButton,8,1,1,2);

    QPushButton *CancelButton = new QPushButton("Cancel");
    connect (CancelButton, SIGNAL(clicked()), this, SLOT(CancelPressed()));
    mainLayout->addWidget(CancelButton,8,0,1,1);
    connect (this, SIGNAL(rejected()), this, SLOT(CancelPressed()));

    setLayout(mainLayout);
}

void ECPDialog::CancelPressed()
{
    this->setVisible(false);
}

void ECPDialog::OKPressed()
{
    genInitObj.robot=Robot(robotCombo->currentIndex());
    emit InsertECP(genInitObj);
    this->setVisible(false);
}

void ECPDialog::add()
{
bool mark=false;
for (int i=0;i<genList->count();i++)
{
    if(genList->item(i)->text().contains(QString().fromStdString(GENERATOR_TYPE_TABLE[genTypeCombo->currentIndex()]), Qt::CaseInsensitive))mark=true;
}
    if (mark)
    {   /*display present*/    }
    else
    {
        genList->addItem(QString().fromStdString(GENERATOR_TYPE_TABLE[genTypeCombo->currentIndex()]).append(" ").append(argLineEdit->text()));
        genInitObj.init_values.push_back(std::make_pair(GeneratorType(genTypeCombo->currentIndex()), argLineEdit->text().toInt()));
    }
}

void ECPDialog::remove()
{
    QList<QListWidgetItem *> toDeleteItems = genList->selectedItems();
    for (int i=0;i<toDeleteItems.size();i++)
    {
        for (std::vector < std::pair<GeneratorType, int> >::iterator iter = genInitObj.init_values.begin(); iter!=genInitObj.init_values.end();iter++)
        {
            if (toDeleteItems[i]->text().contains(QString().fromStdString(GENERATOR_TYPE_TABLE[(*iter).first]), Qt::CaseInsensitive))
            {
                genInitObj.init_values.erase(iter);
                break;
            }
        }
        delete toDeleteItems[i];
    }

}


//***************   MP_DIALOG   ***************//
MPDialog::MPDialog(QWidget * parent): QDialog(parent)
{
    setWindowTitle(tr("MPDialog"));
    QGridLayout * mainLayout = new QGridLayout;

    transmitterCombo = new QComboBox;
    transmitterCombo->addItems(getTransmitterTable());
    transmitterCombo->addItem("None");
    mainLayout->addWidget(transmitterCombo, 0,0,1,2);

    sensorCombo = new QComboBox;
    sensorCombo->addItems(getSensorTable());
    mainLayout->addWidget(sensorCombo,1,0,1,2);

    QPushButton * addButton = new QPushButton("Add");
    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    QPushButton * removeButton = new QPushButton("Remove");
    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    mainLayout->addWidget(addButton,4,0);
    mainLayout->addWidget(removeButton,4,1);

    sensorList = new QListWidget();
    mainLayout->addWidget(sensorList,5, 0, 3, 2);

    QPushButton *OKButton = new QPushButton("OK");
    mainLayout->addWidget(OKButton,8,0,1,2);
    connect (OKButton, SIGNAL(clicked()), this, SLOT(OKPressed()));

    connect (this, SIGNAL(rejected()), this, SLOT(CancelPressed()));
    setLayout(mainLayout);


}

void MPDialog::CancelPressed()
{
    this->setVisible(false);
}

void MPDialog::OKPressed()
{
    std::vector<Sensor> tmp;
    for (int i=0;i<SENSORS_NUMBER;i++)
    {
        if (sensorList->findItems(QString().fromStdString(SENSOR_TABLE[i]), Qt::MatchFlags()).size())
        {
            tmp.push_back(Sensor(i));
        }
    }
    emit InsertMP(tmp, Transmitter(transmitterCombo->currentIndex()));
    this->setVisible(false);
}

void MPDialog::add()
{
    if (sensorList->findItems(QString().fromStdString(SENSOR_TABLE[sensorCombo->currentIndex()]), Qt::MatchFlags()).size())
    {   /*display present*/    }
    else
    {        sensorList->addItem(QString().fromStdString(SENSOR_TABLE[sensorCombo->currentIndex()]));    }
}

void MPDialog::remove()
{
    if (sensorList->findItems(QString().fromStdString(SENSOR_TABLE[sensorCombo->currentIndex()]), Qt::MatchFlags()).size())
    {        delete (sensorList->findItems(QString().fromStdString(SENSOR_TABLE[sensorCombo->currentIndex()]), Qt::MatchFlags()))[0];    }
    else
    {   /*display not present*/ }
}
