#include "StateTypeWidgets.h"
#include <QtGui>

//***************   SYS_INITIALIZATION   ***************//

sysIniWidget::sysIniWidget(QWidget * parent, Model * newmod )
    :MyTypeWidget(parent, newmod )
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
    State->setType(StateType(SYSTEM_INITIALIZATION));

    connect(ecpDialog, SIGNAL(InsertECP(robotInit)), this, SLOT(InsertECP(robotInit)));
    connect(ecpDialog, SIGNAL(ReplaceECP(robotInit)), this, SLOT(ReplaceECP(robotInit)));
    connect (ecpDialog, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));
    connect (mpDialog, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));

    connect(mpDialog, SIGNAL(InsertMP(std::vector<Sensor>,Transmitter)), this, SLOT(InsertMP(std::vector<Sensor>,Transmitter)));

    connect(robotsInitialized, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ItemClicked(QModelIndex)));
}

void sysIniWidget::ItemClicked(QModelIndex ind)
{
    selected = ind.row();
    QString robot = robotsInitialized->currentItem()->text();
    std::vector<robotInit> inits =this->State->getInits();
    for(std::vector<robotInit>::iterator it = inits.begin();it!=inits.end();it++)
    {
        if(ROBOT_TABLE[(*it).robot]==robot.toStdString())
        {
            ecpDialog->openForECP((*it));
            ecpDialog->exec();
        }
    }
}

void sysIniWidget::InsertMP (std::vector<Sensor> sensors, Transmitter trans)
{
    this->State->setSensors(sensors);
    this->State->setTransmitter(trans);
}

void sysIniWidget::InsertECP(robotInit newInit)
{
    std::vector<robotInit> inits = this->State->getInits();
    for (std::vector<robotInit>::iterator it = inits.begin();it!=inits.end();it++)
    {
        if((*it).robot == newInit.robot)
        {
            emit forwardError(QString("Robot exists:").append(QString().fromStdString(ROBOT_TABLE[newInit.robot])));
            return;
        }
    }
    inits.push_back(newInit);
    this->State->setInits(inits);
    this->robotsInitialized->addItem(QString().fromStdString(ROBOT_TABLE[newInit.robot]));
}

void sysIniWidget::ReplaceECP(robotInit newInit)
{
    int x = selected-1;
    std::vector<robotInit> inits = this->State->getInits();
    for (std::vector<robotInit>::iterator it = inits.begin();it!=inits.end();it++)
    {
        if((*it).robot == newInit.robot)
        {
            emit forwardError(QString("Robot exists:").append(QString().fromStdString(ROBOT_TABLE[newInit.robot])));
            return;
        }
    }
    int i=0;
    std::vector<robotInit>::iterator it = inits.begin();
    for (;it!=inits.end()&&i<x;it++,i++)
    {
    }
    inits.erase(it);
    inits.push_back(newInit);
    this->State->setInits(inits);
    this->robotsInitialized->addItem(QString().fromStdString(ROBOT_TABLE[newInit.robot]));

    robotsInitialized->clear();
    foreach(robotInit rob, inits)
    {
        robotsInitialized->addItem(QString().fromStdString(ROBOT_TABLE[rob.robot]));
    }
}

void sysIniWidget::removeECPSection()
{
    QList<QListWidgetItem *> toDeleteItems = robotsInitialized->selectedItems();
    if(toDeleteItems.size()==0)
    {
        emit reportError(QString("No items selected on the list, cannot remove"));
        return;
    }
    std::vector<robotInit> genIniVector;
    genIniVector = this->State->getInits();
    int size = toDeleteItems.size();
    std::vector<robotInit>::iterator tmp_it;
    for (int i=0;i<size;i++)
    {
        for(std::vector<robotInit>::iterator it=genIniVector.begin(); it!=genIniVector.end(); )
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
    ecpDialog->exec();
}
void sysIniWidget::changeMPSection()
{
    mpDialog->exec();
}

BaseState * sysIniWidget::getStateObject()
{
    return new sysInitState(*State);
}

void sysIniWidget::setState(BaseState * st)
{
    delete State;
    State = new sysInitState(*((sysInitState*)st));
    mpDialog->setSensTrans(State->getSensors(), State->getTransmitter());
    this->robotsInitialized->clear();
    for (int i = 0; i< State->getInits().size();i++)
    {
        this->robotsInitialized->addItem(QString().fromStdString(ROBOT_TABLE[(State->getInits())[i].robot]));
    }
}

//***************   RUN_GENERATOR   ***************//

runGenWidget::runGenWidget(QWidget * parent, Model * newmod )
    :MyTypeWidget(parent, newmod )
{
    QVBoxLayout * runGenLayout = new QVBoxLayout;
    robotCombo = new QComboBox(this);
    robotCombo->addItems(getRobotTable());
    runGenLayout->addWidget(robotCombo);
    genTypeCombo = new QComboBox(this);
    genTypeCombo->setFixedWidth(200);
    genTypeCombo->addItems(getGeneratorTypeTable());
    runGenLayout->addWidget(genTypeCombo);
    QLabel * argsLabel = new QLabel("Arguments:");
    argsLineEdit = new QLineEdit;
    runGenLayout->addWidget(argsLabel);
    runGenLayout->addWidget(argsLineEdit);
    QLabel * speechLabel = new QLabel("Speech:");
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

    coordDialog = new CoordDialog(this);
    coordDialog->setVisible(false);

    State = new RunGenState();
    State->getCoords()->setMotionType(MotionType(0));
    State->getCoords()->setCoordType(CoordType(0));
    State->setType(StateType(RUN_GENERATOR));

    connect(coordDialog, SIGNAL(InsertCoords(Coordinates*)), this, SLOT(CoordsInsert(Coordinates*)));
    connect(coordDialog, SIGNAL(reportError(QString)), this, SLOT(forwardError(QString)));
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
    coordDialog->exec();
}

BaseState * runGenWidget::getStateObject()
{
    Coordinates * tmp = State->getCoords();
    State->setArgs(argsLineEdit->text());
    State->setSpeech(speechLineEdit->text());
    State->setGenType(GeneratorType(genTypeCombo->currentIndex()));
    State->setRobot(Robot(robotCombo->currentIndex()));
    State->setFilePath(trjFileName->text());
    State->setCoords(tmp);
    return new RunGenState(*State);
}

void runGenWidget::setState(BaseState * st)
{
    delete State;
    State = new RunGenState(*((RunGenState*)st));
    robotCombo->setCurrentIndex(State->getRobot());
    argsLineEdit->setText(State->getArgs());
    speechLineEdit->setText(State->getSpeech());
    genTypeCombo->setCurrentIndex(State->getGenType());
    trjFileName->setText(State->getFilePath());
    coordDialog->setCoords(new Coordinates(*(State->getCoords())));
    coordDialog->coordsUpdated();
}

//***************   EMPTY_GEN_FOR_SET   ***************//

emptyGenForSetWidget::emptyGenForSetWidget(QWidget * parent, Model * newmod )
    :MyTypeWidget(parent, newmod )
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

    /*QLabel *SecondSetLabel = new QLabel("Second Set:");
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
*/
     setLayout(emptyGenLayout);

     State = new EmptyGenForSetState();
     State->setType(StateType(EMPTY_GEN_FOR_SET));
}

void emptyGenForSetWidget::addFirst()
{
    if (FirstRobotList->findItems(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {        emit reportError(QString("this robot is already in the first set: ").append(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()])));    }
    else
    {        FirstRobotList->addItem(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]));    }
}

void emptyGenForSetWidget::removeFirst()
{    
    if(FirstRobotList->selectedItems().size()==0)
    {
        emit reportError(QString("No items selected on the list, cannot remove"));
        return;
    }
    foreach(QListWidgetItem * x, FirstRobotList->selectedItems())
    {
        QString text = x->text();
        if (FirstRobotList->findItems(text, Qt::MatchFlags()).size())
        {        delete (FirstRobotList->findItems(text, Qt::MatchFlags())[0]);    }
    }
}

/*void emptyGenForSetWidget::addSecond()
{
    if (SecondRobotList->findItems(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {        emit reportError(QString("this robot is already in the first set: ").append(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()])));    }
    else
    {        SecondRobotList->addItem(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()]));    }
}

void emptyGenForSetWidget::removeSecond()
{
    if (SecondRobotList->findItems(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {        delete (SecondRobotList->findItems(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()]), Qt::MatchFlags()))[0];    }
    else
    {        emit reportError(QString("this robot is not in the first set: ").append(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()])));    }
}
*/
BaseState * emptyGenForSetWidget::getStateObject()
{
    RobotSet tmp;
    tmp = this->State->getSet();
    tmp.first.clear();
  //  tmp.second.clear();
    for (int i=0;i<ROBOTS_NUMBER;i++)
    {
        if (FirstRobotList->findItems(QString().fromStdString(ROBOT_TABLE[i]), Qt::MatchFlags()).size())
        {
            tmp.first.push_back(Robot(i));
        }
    /*    if (SecondRobotList->findItems(QString().fromStdString(ROBOT_TABLE[i]), Qt::MatchFlags()).size())
        {
            tmp.second.push_back(Robot(i));
        }*/
    }
    this->State->setSet(tmp);
    if(tmp.first.size()==0)
    {
        reportError(QString("The set can't be empty in EmptyGenForSet state"));
        return NULL;
    }
    return new EmptyGenForSetState(*State);
}

void emptyGenForSetWidget::setState(BaseState * st)
{
    delete State;
    State = new EmptyGenForSetState(*((EmptyGenForSetState*)st));
    FirstRobotList->clear();
    //SecondRobotList->clear();
    RobotSet set = State->getSet();
    std::vector<Robot> robots = set.first;
    foreach(Robot rob, robots)
    {
        FirstRobotList->addItem(QString().fromStdString(ROBOT_TABLE[rob]));
    }
    /*robots = set.second;
    foreach(Robot rob, robots)
    {
        SecondRobotList->addItem(QString().fromStdString(ROBOT_TABLE[rob]));
    }*/
}

//***************   EMPTY_GEN   ***************//

emptyGenWidget::emptyGenWidget(QWidget * parent, Model * newmod )
    :MyTypeWidget(parent, newmod )
{
    QVBoxLayout * emptyGenLayout = new QVBoxLayout;
    QLabel *argLabel = new QLabel(tr("Argument:"));
    argLineEdit = new QLineEdit();
    argLineEdit->setValidator(new QIntValidator(argLineEdit));

    emptyGenLayout->addWidget(argLabel);
    emptyGenLayout->addWidget(argLineEdit);

    QLabel *SetLabel = new QLabel(tr("Robot:"));
    emptyGenLayout->addWidget(SetLabel);

    RobotCombo = new QComboBox(this);
    RobotCombo->setFixedWidth(200);
    RobotCombo->addItems(getRobotTable());
    emptyGenLayout->addWidget(RobotCombo);

    setLayout(emptyGenLayout);

    State = new EmptyGenState();
    State->setType(StateType(EMPTY_GEN));
}

BaseState * emptyGenWidget::getStateObject()
{
    this->State->setRobot(Robot(RobotCombo->currentIndex()));
    this->State->setArgument(argLineEdit->text());
    return new EmptyGenState(*State);
}

void emptyGenWidget::setState(BaseState * st)
{
    delete State;
    State = new EmptyGenState(*((EmptyGenState*)st));
    argLineEdit->setText(State->getArgument());
    RobotCombo->setCurrentIndex(State->getRobot());
}

//***************   WAIT_GEN   ***************//

waitStateWidget::waitStateWidget(QWidget * parent, Model * newmod )
    :MyTypeWidget(parent, newmod )
{
    QVBoxLayout * waitLayout = new QVBoxLayout;

    QLabel *TimeLabel = new QLabel(tr("TimeSpan (ms.)"));
    timeSpan = new QLineEdit;
    timeSpan->setValidator(new QIntValidator(0, 999999999, timeSpan));
    waitLayout->addWidget(TimeLabel);
    waitLayout->addWidget(timeSpan);

    setLayout(waitLayout);
    State = new WaitState();
    State->setType(StateType(WAIT));
}

BaseState * waitStateWidget::getStateObject()
{
    this->State->setTimespan(timeSpan->text().toLongLong());
    return new WaitState(*State);
}

void waitStateWidget::setState(BaseState * st)
{
    delete State;
    State = new WaitState(*((WaitState*)st));
    char tab[20];
    sprintf (tab, "%lld", State->getTimespan());
    timeSpan->setText(QString().fromStdString(tab));
}

//***************   STOP_GEN   ***************//

stopGenWidget::stopGenWidget(QWidget * parent, Model * newmod )
    :MyTypeWidget(parent, newmod )
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
     State->setType(StateType(STOP_GEN));
}

void stopGenWidget::add()
{
    if (RobotList->findItems(QString().fromStdString(ROBOT_TABLE[RobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {        emit reportError(QString("this robot is already in the set: ").append(QString().fromStdString(ROBOT_TABLE[RobotCombo->currentIndex()])));    }
    else
    {        RobotList->addItem(QString().fromStdString(ROBOT_TABLE[RobotCombo->currentIndex()]));    }
}

void stopGenWidget::remove()
{
    if(RobotList->selectedItems().size()==0)
    {
        emit reportError(QString("No items selected on the list, cannot remove"));
        return;
    }
    foreach(QListWidgetItem * x, RobotList->selectedItems())
    {
        QString text = x->text();
        if (RobotList->findItems(text, Qt::MatchFlags()).size())
        {        delete (RobotList->findItems(text, Qt::MatchFlags())[0]);    }
    }
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
    if(tmp.first.size()==0)
    {
        reportError(QString("The set cannot be empty in StopGen state"));
        return NULL;
    }
    return new StopGenState(*State);
}

void stopGenWidget::setState(BaseState * st)
{
    delete State;
    State = new StopGenState(*((StopGenState*)st));
    RobotList->clear();
    RobotSet set = State->getSet();
    std::vector<Robot> robots = set.first;
    foreach(Robot rob, robots)
    {
        RobotList->addItem(QString().fromStdString(ROBOT_TABLE[rob]));
    }
}

//***************   SENSOR_INI_GEN   ***************//

iniSensorWidget::iniSensorWidget(QWidget * parent, Model * newmod )
    :MyTypeWidget(parent, newmod )
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
    State->setType(StateType(INITIATE_SENSOR_READING));
}

BaseState * iniSensorWidget::getStateObject()
{
    this->State->setSensor(Sensor(SensorCombo->currentIndex()));
    return new InitiateSensorState(*State);
}

void iniSensorWidget::setState(BaseState * st)
{
    delete State;
    State = new InitiateSensorState(*((InitiateSensorState*)st));
    SensorCombo->setCurrentIndex(State->getSensor());
}

//***************   GET_SENSOR_GEN   ***************//

getSensorWidget::getSensorWidget(QWidget * parent, Model * newmod )
    :MyTypeWidget(parent, newmod )
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
    State->setType(StateType(GET_SENSOR_READING));
}

BaseState * getSensorWidget::getStateObject()
{
    this->State->setSensor(Sensor(SensorCombo->currentIndex()));
    return new GetSensorState(*State);
}

void getSensorWidget::setState(BaseState * st)
{
    delete State;
    State = new GetSensorState(*((GetSensorState*)st));
    SensorCombo->setCurrentIndex(State->getSensor());
}


//***********************************************   DIALOGS   ***********************************************//




//***************   POSE_DIALOG   ***************//

CoordDialog::CoordDialog(QWidget * parent): QDialog(parent)
{
    setWindowTitle(tr("Coordinates"));
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

void CoordDialog::AddPose()
{
    Pose * tmp = new Pose();
    std::vector<double> a, v, c;
    int i = 0;
    for (;i<7;i++)
    {
        if(coordEdit[i]->text().isEmpty() || velEdit[i]->text().isEmpty() || accEdit[i]->text().isEmpty())
        {
            break;
        }
        else
        {
            a.push_back(accEdit[i]->text().toDouble());
            v.push_back(velEdit[i]->text().toDouble());
            c.push_back(coordEdit[i]->text().toDouble());
        }
    }

    if(poseList->count()!=0&&i!=num)
    {
        emit reportError(QString("The pose you're trying to aadd has a different length than the previous one(s)"));
        return;
    }
    else
    {
        num = i;
    }

    if(i!=0)
    {
        tmp->setA(a);
        tmp->setV(v);
        tmp->setC(c);
        std::vector<Pose *> pos_vec= coords->getPoses();
        pos_vec.push_back(tmp);
        coords->setPoses(pos_vec);
        QString str;
        char tab[20];
        sprintf(tab, "Pose: C:", i);
        str.append(QString().fromStdString(tab));
        for(int j=0;j<i;j++)
        {
            sprintf(tab, " %3.2f", c[j]);
            str.append(QString().fromStdString(tab));
        }
        str.append(QString(" V:"));
        for(int j=0;j<i;j++)
        {
            sprintf(tab, " %3.2f", v[j]);
            str.append(QString().fromStdString(tab));
        }
        str.append(QString(" A:"));
        for(int j=0;j<i;j++)
        {
            sprintf(tab, " %3.2f", a[j]);
            str.append(QString().fromStdString(tab));
        }
        poseList->addItem(str);
    }
}

void CoordDialog::PoseOK()
{
    coords->setCoordType(CoordType(coordTypeCombo->currentIndex()));
    coords->setMotionType(MotionType(motionTypeCombo->currentIndex()));
    Coordinates * tmp = new Coordinates(*coords);
    emit InsertCoords(tmp);
    this->setVisible(false);
}

void CoordDialog::PoseCancel()
{
    this->setVisible(false);
}

void CoordDialog::PosesReset()
{
    num=0;
    poseList->clear();
    delete coords;
    coords = new Coordinates();
}

void CoordDialog::coordsUpdated()
{
    coordTypeCombo->setCurrentIndex((int)this->coords->getCoordType());
    motionTypeCombo->setCurrentIndex((int)this->coords->getMotionType());
    poseList->clear();
    foreach(Pose * pose, this->coords->getPoses())
    {
        QString str;
        char tab[20];
        int i = pose->getC().size();
        sprintf(tab, "Pose: C:", i);
        str.append(QString().fromStdString(tab));
        for(int j=0;j<i;j++)
        {
            sprintf(tab, " %3.2f", pose->getC()[j]);
            str.append(QString().fromStdString(tab));
        }
        str.append(QString(" V:"));
        for(int j=0;j<i;j++)
        {
            sprintf(tab, " %3.2f", pose->getV()[j]);
            str.append(QString().fromStdString(tab));
        }
        str.append(QString(" A:"));
        for(int j=0;j<i;j++)
        {
            sprintf(tab, " %3.2f", pose->getA()[j]);
            str.append(QString().fromStdString(tab));
        }
        poseList->addItem(str);
        num = i;
    }
}

//***************   ECP_DIALOG   ***************//
ECPDialog::ECPDialog(QWidget * parent): QDialog(parent)
{
    setWindowTitle(tr("ECPDialog"));
    QGridLayout * mainLayout = new QGridLayout;
    QLabel * RobotLabel = new QLabel("Robot:");
    mainLayout->addWidget(RobotLabel,0,0,1,3);

    robotCombo = new QComboBox;
    robotCombo->addItems(getRobotTable());
    mainLayout->addWidget(robotCombo, 1,0,1,3);


    QLabel * GenLabel = new QLabel("Generator:");
    mainLayout->addWidget(GenLabel,2,0,1,3);

    genTypeCombo = new QComboBox;
    genTypeCombo->addItems(getGeneratorTypeTable());
    mainLayout->addWidget(genTypeCombo,3,0,1,3);
    QLabel * argLabel = new QLabel("Init argument:");
    mainLayout->addWidget(argLabel, 4,0,1,3);
    argLineEdit = new QLineEdit();
    argLineEdit->setValidator(new QIntValidator(argLineEdit));
    mainLayout->addWidget(argLineEdit,5,0,1,3);

    QPushButton * addButton = new QPushButton("Add");
    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    QPushButton * removeButton = new QPushButton("Remove selected");
    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    mainLayout->addWidget(addButton,6,0);
    mainLayout->addWidget(removeButton,6,1, 1, 2);

    genList = new QListWidget();
    mainLayout->addWidget(genList,7, 0, 3, 3);

    QPushButton *OKButton = new QPushButton("OK");
    connect (OKButton, SIGNAL(clicked()), this, SLOT(OKPressed()));
    mainLayout->addWidget(OKButton,10,1,1,2);

    QPushButton *CancelButton = new QPushButton("Cancel");
    connect (CancelButton, SIGNAL(clicked()), this, SLOT(CancelPressed()));
    mainLayout->addWidget(CancelButton,10,0,1,1);
    connect (this, SIGNAL(rejected()), this, SLOT(CancelPressed()));

    setLayout(mainLayout);
    edited=false;
}

void ECPDialog::CancelPressed()
{
    edited=false;
    this->setVisible(false);
}

void ECPDialog::OKPressed()
{
    if(!edited)
    {
        robotInitObj.robot=Robot(robotCombo->currentIndex());
        emit InsertECP(robotInitObj);
    }
    else
    {
        robotInitObj.robot=Robot(robotCombo->currentIndex());
        emit ReplaceECP(robotInitObj);
    }
    edited=false;
    this->setVisible(false);
}

void ECPDialog::add()
{
    bool mark=false;
    if(argLineEdit->text().size()==0)
    {
        reportError(QString("Generator needs to have arguments"));
        return;
    }
    for (int i=0;i<genList->count();i++)
    {
        if(genList->item(i)->text().contains(QString().fromStdString(GENERATOR_TYPE_TABLE[genTypeCombo->currentIndex()]), Qt::CaseInsensitive))mark=true;
    }
    if (mark)
    {   emit reportError(QString("This generator is already initialized: ").append(QString().fromStdString(GENERATOR_TYPE_TABLE[genTypeCombo->currentIndex()])));    }
    else
    {
        genList->addItem(QString().fromStdString(GENERATOR_TYPE_TABLE[genTypeCombo->currentIndex()]).append(" ").append(argLineEdit->text()));
        robotInitObj.init_values.push_back(std::make_pair(GeneratorType(genTypeCombo->currentIndex()), argLineEdit->text().toInt()));
    }
}

void ECPDialog::openForECP(robotInit robotIni)
{
    edited=true;
    robotInitObj=robotIni;
    genList->clear();
    robotCombo->setCurrentIndex(robotIni.robot);
    for (std::vector < std::pair<GeneratorType, int> >::iterator it = robotIni.init_values.begin(); it!=robotIni.init_values.end();it++)
    {
        char str[10];
        sprintf(str, "%d", (*it).second);
        genList->addItem(QString().fromStdString(GENERATOR_TYPE_TABLE[(*it).first]).append(" ").append(QString().fromStdString(str) ));
    }
}

void ECPDialog::remove()
{
    QList<QListWidgetItem *> toDeleteItems = genList->selectedItems();
    for (int i=0;i<toDeleteItems.size();i++)
    {
        for (std::vector < std::pair<GeneratorType, int> >::iterator iter = robotInitObj.init_values.begin(); iter!=robotInitObj.init_values.end();iter++)
        {
            if (toDeleteItems[i]->text().contains(QString().fromStdString(GENERATOR_TYPE_TABLE[(*iter).first]), Qt::CaseInsensitive))
            {
                robotInitObj.init_values.erase(iter);
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
QLabel * TransmitterLabel = new QLabel("Transmitter:");
mainLayout->addWidget(TransmitterLabel,0,0,1,2);
    transmitterCombo = new QComboBox;
    transmitterCombo->addItems(getTransmitterTable());
    transmitterCombo->addItem("None");
    mainLayout->addWidget(transmitterCombo, 1,0,1,2);


    QLabel * SensorsLabel = new QLabel("Sensors:");
    mainLayout->addWidget(SensorsLabel,2,0,1,2);

    sensorCombo = new QComboBox;
    sensorCombo->addItems(getSensorTable());
    mainLayout->addWidget(sensorCombo,3,0,1,2);

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

void MPDialog::setSensTrans(std::vector<Sensor> sens, Transmitter tran)
{
    sensorList->clear();
    for (int i = 0; i< sens.size();i++)
    {
        sensorList->addItem(QString().fromStdString(SENSOR_TABLE[sens[i]]));
    }
    transmitterCombo->setCurrentIndex(tran);
}

void MPDialog::add()
{
    if (sensorList->findItems(QString().fromStdString(SENSOR_TABLE[sensorCombo->currentIndex()]), Qt::MatchFlags()).size())
    {   emit reportError(QString("This sensor is already initialized: ").append(QString().fromStdString(SENSOR_TABLE[sensorCombo->currentIndex()])));}
    else
    {        sensorList->addItem(QString().fromStdString(SENSOR_TABLE[sensorCombo->currentIndex()]));    }
}

void MPDialog::remove()
{

    if(sensorList->selectedItems().size()==0)
    {
        emit reportError(QString("No items selected on the list, cannot remove"));
        return;
    }
    foreach(QListWidgetItem * x, sensorList->selectedItems())
    {
        QString text = x->text();
        if (sensorList->findItems(text, Qt::MatchFlags()).size())
        {        delete (sensorList->findItems(text, Qt::MatchFlags())[0]);    }
    }
}

