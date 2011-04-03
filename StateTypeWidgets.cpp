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

}
void sysIniWidget::removeECPSection()
{
    QList<QListWidgetItem *> toDeleteItems = robotsInitialized->selectedItems();
    int size = toDeleteItems.size();
    for (int i=0;i<size;i++)
    {
        delete toDeleteItems[i];
    }

}
void sysIniWidget::createECPSection()
{
    ecpDialog->exec();
    ecpDialog->setVisible(true);
}
void sysIniWidget::changeMPSection()
{
    mpDialog->exec();
    mpDialog->setVisible(true);
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








    QPushButton * runGenAddPoseButton = new QPushButton (tr("Add Pose"));
    connect(runGenAddPoseButton, SIGNAL(clicked()), this, SLOT(showAddPosesDialog()));
 //connectButton with dialog box
    runGenLayout->addWidget(runGenAddPoseButton);
    setLayout(runGenLayout);

    poseDialog = new PoseDialog(this);
    poseDialog->setVisible(false);

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

    //poseDialog->show();
    poseDialog->setVisible(true);
    poseDialog->exec();
    //create a dialog with poses.
}

void runGenWidget::PoseAdd()
{
    poseDialog->setVisible(false);
}



void runGenWidget::PosesReset()
{

}

void runGenWidget::PoseCancel()
{

}

BaseState * runGenWidget::getStateObject()
{
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
}


void emptyGenForSetWidget::addFirst()
{
    if (FirstRobotList->findItems(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {

    }
    else
    {
        FirstRobotList->addItem(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]));
    }
}

void emptyGenForSetWidget::removeFirst()
{
    if (FirstRobotList->findItems(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {
        delete (FirstRobotList->findItems(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]), Qt::MatchFlags()))[0];
    }
}

void emptyGenForSetWidget::addSecond()
{
    if (SecondRobotList->findItems(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {

    }
    else
    {
        SecondRobotList->addItem(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()]));
    }
}

void emptyGenForSetWidget::removeSecond()
{
    if (SecondRobotList->findItems(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {
        delete (SecondRobotList->findItems(QString().fromStdString(ROBOT_TABLE[SecondRobotCombo->currentIndex()]), Qt::MatchFlags()))[0];
    }
}

BaseState * emptyGenForSetWidget::getStateObject()
{
    return new EmptyGenForSetState(*State);
}

//***************   EMPTY_GEN   ***************//


emptyGenWidget::emptyGenWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * emptyGenLayout = new QVBoxLayout;




    QLabel *FirstSetLabel = new QLabel(tr("Robot:"));
    emptyGenLayout->addWidget(FirstSetLabel);


    RobotCombo = new QComboBox(this);
    RobotCombo->setFixedWidth(200);
    RobotCombo->addItems(getRobotTable());
    emptyGenLayout->addWidget(RobotCombo);


     setLayout(emptyGenLayout);
}

BaseState * emptyGenWidget::getStateObject()
{
    return new EmptyGenState(*State);
}


//***************   WAIT_GEN   ***************//


waitStateWidget::waitStateWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * waitLayout = new QVBoxLayout;


    QLabel *TimeLabel = new QLabel(tr("TimeSpan"));
    timeSpan = new QLineEdit;
    waitLayout->addWidget(TimeLabel);
    waitLayout->addWidget(timeSpan);
     setLayout(waitLayout);
}

BaseState * waitStateWidget::getStateObject()
{
    return new WaitState(*State);
}

//***************   STOP_GEN   ***************//

stopGenWidget::stopGenWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * stopGenLayout = new QVBoxLayout;



    //buttons add+remove

    QLabel *FirstSetLabel = new QLabel(tr("First Set:"));
    stopGenLayout->insertWidget(0,FirstSetLabel);

    FirstRobotList = new QListWidget(this);
    stopGenLayout->insertWidget(1,FirstRobotList);

    FirstRobotCombo = new QComboBox(this);
    FirstRobotCombo->setFixedWidth(200);
    FirstRobotCombo->addItems(getRobotTable());

    stopGenLayout->insertWidget(2,FirstRobotCombo);



    QHBoxLayout * firstButtonsLayout = new QHBoxLayout;
    QPushButton * addFirstButton = new QPushButton("Add");
    connect(addFirstButton, SIGNAL(clicked()), this, SLOT(addFirst()));
    QPushButton * removeFirstButton = new QPushButton("Remove");
    connect(removeFirstButton, SIGNAL(clicked()), this, SLOT(removeFirst()));
    firstButtonsLayout->addWidget(addFirstButton);
    firstButtonsLayout->addWidget(removeFirstButton);
    stopGenLayout->insertLayout(3,firstButtonsLayout);



     setLayout(stopGenLayout);
}

void stopGenWidget::addFirst()
{
    //FirstRobotList->selectedItems();
    if (FirstRobotList->findItems(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {

    }
    else
    {
        FirstRobotList->addItem(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]));
    }
}

void stopGenWidget::removeFirst()
{
    if (FirstRobotList->findItems(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]), Qt::MatchFlags()).size())
    {
        delete (FirstRobotList->findItems(QString().fromStdString(ROBOT_TABLE[FirstRobotCombo->currentIndex()]), Qt::MatchFlags()))[0];
    }

}
BaseState * stopGenWidget::getStateObject()
{
    return new StopGenState(*State);
}

//***************   SENSOR_INI_GEN   ***************//

iniSensorWidget::iniSensorWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * iniSensorLayout = new QVBoxLayout;



    //buttons add+remove

    QLabel *FirstSetLabel = new QLabel(tr("Sensor:"));
    iniSensorLayout->addWidget(FirstSetLabel);


    SensorCombo = new QComboBox(this);
    SensorCombo->setFixedWidth(200);
    SensorCombo->addItems(getSensorTable());
    iniSensorLayout->addWidget(SensorCombo);


     setLayout(iniSensorLayout);
}

BaseState * iniSensorWidget::getStateObject()
{
    return new InitiateSensorState(*State);
}

//***************   GET_SENSOR_GEN   ***************//
getSensorWidget::getSensorWidget(QWidget * parent)
    :MyTypeWidget(parent)
{
    QVBoxLayout * getSensorLayout = new QVBoxLayout;

    QStringList items;
    for (int i=0;i<SENSORS_NUMBER;i++)
    {
        items<<QString().fromStdString(SENSOR_TABLE[i]);
    }

    //buttons add+remove

    QLabel *FirstSetLabel = new QLabel(tr("Sensor:"));
    getSensorLayout->addWidget(FirstSetLabel);


    SensorCombo = new QComboBox(this);
    SensorCombo->setFixedWidth(200);
    SensorCombo->addItems(getSensorTable());
    getSensorLayout->addWidget(SensorCombo);


     setLayout(getSensorLayout);
}

BaseState * getSensorWidget::getStateObject()
{
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
//connect
    QPushButton * rmPoseButt = new QPushButton("Remove");
    mainLayout->addWidget(rmPoseButt,7,1);
//connect

    QLabel * coordLabel = new QLabel("Coordinates");
    mainLayout->addWidget(coordLabel, 0, 2);
    QLabel * velocityLabel = new QLabel("Velocities");
    mainLayout->addWidget(velocityLabel, 0, 3);
    QLabel * accelerationLabel = new QLabel("Accelerations");
    mainLayout->addWidget(accelerationLabel, 0, 4);

    for (int i = 0;i<7;i++)
    {
        coordEdit.push_back(new QLineEdit);
        coordEdit[i]->setValidator(new QDoubleValidator(-99999.0,99999.0, 5,coordEdit[i]));
        coordEdit[i]->setMaximumWidth(80);
        mainLayout->addWidget(coordEdit[i], i+1, 2);


        velEdit.push_back(new QLineEdit);
        velEdit[i]->setValidator(new QDoubleValidator(-99999.0,99999.0, 5,velEdit[i]));
        velEdit[i]->setMaximumWidth(80);
        mainLayout->addWidget(velEdit[i], i+1, 3);


        accEdit.push_back(new QLineEdit);
        accEdit[i]->setValidator(new QDoubleValidator(-99999.0,99999.0, 5,accEdit[i]));
        accEdit[i]->setMaximumWidth(80);
        mainLayout->addWidget(accEdit[i], i+1, 4);
    }

    QPushButton * resetAllButton = new QPushButton ("Reset all poses");
    connect(resetAllButton, SIGNAL(clicked()), this->parent(), SLOT(PosesReset()) );
    mainLayout->addWidget(resetAllButton, 8, 0, 1, 2);


    QPushButton * cancelButton = new QPushButton ("Cancel");
    connect(cancelButton, SIGNAL(clicked()), this->parent(), SLOT(PoseCancel()) );
    mainLayout->addWidget(cancelButton, 8, 2);

    QPushButton * addButton = new QPushButton ("OK");
    connect(addButton, SIGNAL(clicked()), this->parent(), SLOT(PoseAdd()) );
    mainLayout->addWidget(addButton, 8, 3, 1, 2);


    this->setLayout(mainLayout);
}

//***************   ECP_DIALOG   ***************//
ECPDialog::ECPDialog(QWidget * parent): QDialog(parent)
{
    setWindowTitle(tr("ECPDialog"));
    QGridLayout * mainLayout = new QGridLayout;

    robotCombo = new QComboBox;
    robotCombo->addItems(getRobotTable());
    mainLayout->addWidget(robotCombo, 0,0,1,2);

    genTypeCombo = new QComboBox;
    genTypeCombo->addItems(getGeneratorTypeTable());
    mainLayout->addWidget(genTypeCombo,1,0,1,2);
    QLabel * argLabel = new QLabel("Init argument:");
    mainLayout->addWidget(argLabel, 2,0,1,2);
    argLineEdit = new QLineEdit();
    argLineEdit->setValidator(new QIntValidator(argLineEdit));
    mainLayout->addWidget(argLineEdit,3,0,1,2);


    QPushButton * addButton = new QPushButton("Add");
    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    QPushButton * removeButton = new QPushButton("Remove");
    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    mainLayout->addWidget(addButton,4,0);
    mainLayout->addWidget(removeButton,4,1);


    genList = new QListWidget();
    mainLayout->addWidget(genList,5, 0, 3, 2);

    QPushButton *OKButton = new QPushButton("OK");
    mainLayout->addWidget(OKButton,8,0,1,2);


    setLayout(mainLayout);




}

void ECPDialog::add()
{
    if (genList->findItems(QString().fromStdString(GENERATOR_TYPE_TABLE[genTypeCombo->currentIndex()]), Qt::MatchFlags()).size())
    {

    }
    else
    {
        genList->addItem(QString().fromStdString(GENERATOR_TYPE_TABLE[genTypeCombo->currentIndex()]));
    }
}

void ECPDialog::remove()
{
    if (genList->findItems(QString().fromStdString(GENERATOR_TYPE_TABLE[genTypeCombo->currentIndex()]), Qt::MatchFlags()).size())
    {
        delete (genList->findItems(QString().fromStdString(GENERATOR_TYPE_TABLE[genTypeCombo->currentIndex()]), Qt::MatchFlags()))[0];
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


    setLayout(mainLayout);

}

void MPDialog::add()
{
    if (sensorList->findItems(QString().fromStdString(SENSOR_TABLE[sensorCombo->currentIndex()]), Qt::MatchFlags()).size())
    {

    }
    else
    {
        sensorList->addItem(QString().fromStdString(SENSOR_TABLE[sensorCombo->currentIndex()]));
    }
}

void MPDialog::remove()
{
    if (sensorList->findItems(QString().fromStdString(SENSOR_TABLE[sensorCombo->currentIndex()]), Qt::MatchFlags()).size())
    {
        delete (sensorList->findItems(QString().fromStdString(SENSOR_TABLE[sensorCombo->currentIndex()]), Qt::MatchFlags()))[0];
    }
}
