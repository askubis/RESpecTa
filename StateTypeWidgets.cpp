#include "StateTypeWidgets.h"
#include <QtGui>

//dal kazdego umiescic w nim jego Typ Stanu i zrobic funkcje Get oraz Set


//***************   SYS_INITIALIZATION   ***************//

sysIniWidget::sysIniWidget(QWidget * parent)
    :QWidget(parent)
{
    QVBoxLayout * sysIniLayout = new QVBoxLayout;
    QPushButton * iniAddRobotButton = new QPushButton ("Create ECP section");
    connect (iniAddRobotButton, SIGNAL(clicked()), this, SLOT(createECPSection()));
 //connectButton with showing a dialog box
    sysIniLayout->addWidget(iniAddRobotButton);

    QPushButton * iniAddMPButton = new QPushButton ("Create MP section");
    connect (iniAddMPButton, SIGNAL(clicked()), this, SLOT(createMPSection()));
 //connectButton with showing a dialog box
    sysIniLayout->addWidget(iniAddMPButton);

    this->setLayout(sysIniLayout);


}

void sysIniWidget::createECPSection()
{
    //show edit dialog with robot combobox and checkbox+label+intEdit for every generator.
}
void sysIniWidget::createMPSection()
{
    //show edit dialog with things included in the MP section
}



//***************   RUN_GENERATOR   ***************//

runGenWidget::runGenWidget(QWidget * parent)
    :QWidget(parent)
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


//***************   EMPTY_GEN_FOR_SET   ***************//


emptyGenForSetWidget::emptyGenForSetWidget(QWidget * parent)
    :QWidget(parent)
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


//***************   EMPTY_GEN   ***************//


emptyGenWidget::emptyGenWidget(QWidget * parent)
    :QWidget(parent)
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


//***************   WAIT_GEN   ***************//


waitStateWidget::waitStateWidget(QWidget * parent)
    :QWidget(parent)
{
    QVBoxLayout * waitLayout = new QVBoxLayout;


    QLabel *TimeLabel = new QLabel(tr("TimeSpan"));
    timeSpan = new QLineEdit;
    waitLayout->addWidget(TimeLabel);
    waitLayout->addWidget(timeSpan);
     setLayout(waitLayout);
}

//***************   STOP_GEN   ***************//

stopGenWidget::stopGenWidget(QWidget * parent)
    :QWidget(parent)
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

//***************   SENSOR_INI_GEN   ***************//

iniSensorWidget::iniSensorWidget(QWidget * parent)
    :QWidget(parent)
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

//***************   GET_SENSOR_GEN   ***************//
getSensorWidget::getSensorWidget(QWidget * parent)
    :QWidget(parent)
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
