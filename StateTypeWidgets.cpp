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
    QStringList items;
    items << tr("ECP_GEN_TEACH_IN") << tr("ECP_GEN_NEWSMOOTH") << tr("ECP_GEN_WEIGHT_MEASURE") << tr("ECP_GEN_TRANSPARENT")
            << tr("ECP_GEN_TFF_NOSE_RUN") << tr("ECP_GEN_BIAS_EDP_FORCE") << tr("ECP_GEN_TFF_RUBIK_GRAB")
            << tr("ECP_GEN_TFF_RUBIK_FACE_ROTATE") << tr("ECP_ST_GRIPPER_OPENING");
    genTypeCombo = new QComboBox(this);
    genTypeCombo->setFixedWidth(200);
    genTypeCombo->addItems(items);
    //connect(stateTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setStateSubclass(int)));
    argsLabel = new QLabel("Arguments:");
    argsLineEdit = new QLineEdit;
    runGenLayout->addWidget(argsLabel);
    runGenLayout->addWidget(argsLineEdit);
    speechLabel = new QLabel("Speech:");
    speechLineEdit = new QLineEdit;
    runGenLayout->addWidget(speechLabel);
    runGenLayout->addWidget(speechLineEdit);



    QPushButton * runGenAddPoseButton = new QPushButton (tr("Add Pose"));
 //connectButton with dialog box
    runGenLayout->addWidget(runGenAddPoseButton);
    setLayout(runGenLayout);

}

void runGenWidget::addPoses()
{
    //create a dialog with poses.
}


//***************   EMPTY_GEN_FOR_SET   ***************//


emptyGenForSetWidget::emptyGenForSetWidget(QWidget * parent)
    :QWidget(parent)
{
    QVBoxLayout * emptyGenLayout = new QVBoxLayout;

    QStringList items;
    items << tr("ROBOT_UNDEFINED") << tr("ROBOT_IRP6OT_M") << tr("ROBOT_IRP6P_M") << tr("ROBOT_FESTIVAL")
            << tr("ROBOT_CONVEYOR") << tr(" ROBOT_SPEAKER") << tr("ROBOT_IRP6_MECHATRONIKA") << tr("ROBOT_ELECTRON")
            << tr("ROBOT_HAND") << tr("ROBOT_SPEECHRECOGNITION");


    QLabel *FirstSetLabel = new QLabel(tr("First Set:/nxxx"));
    emptyGenLayout->addWidget(FirstSetLabel);
    //labels with setText

    FirstRobotCombo = new QComboBox(this);
    FirstRobotCombo->setFixedWidth(200);
    FirstRobotCombo->addItems(items);
    emptyGenLayout->addWidget(FirstRobotCombo);

    QHBoxLayout * firstButtonsLayout = new QHBoxLayout;
    QPushButton * addFirstButton = new QPushButton("Add");
    QPushButton * removeFirstButton = new QPushButton("Remove");
    firstButtonsLayout->addWidget(addFirstButton);
    firstButtonsLayout->addWidget(removeFirstButton);
    emptyGenLayout->addLayout(firstButtonsLayout);


    QLabel *SecondSetLabel = new QLabel("Second Set:");
    emptyGenLayout->addWidget(SecondSetLabel);

    SecondRobotCombo = new QComboBox(this);
    SecondRobotCombo->setFixedWidth(200);
    SecondRobotCombo->addItems(items);
    emptyGenLayout->addWidget(FirstRobotCombo);
    QHBoxLayout * secondButtonsLayout = new QHBoxLayout;
    QPushButton * addSecondButton = new QPushButton("Add");
    QPushButton * removeSecondButton = new QPushButton("Remove");
    secondButtonsLayout->addWidget(addSecondButton);
    secondButtonsLayout->addWidget(removeSecondButton);
    emptyGenLayout->addLayout(secondButtonsLayout);

     setLayout(emptyGenLayout);
}

//***************   EMPTY_GEN   ***************//


emptyGenWidget::emptyGenWidget(QWidget * parent)
    :QWidget(parent)
{
    QVBoxLayout * emptyGenLayout = new QVBoxLayout;

    QStringList items;
    items << tr("ROBOT_UNDEFINED") << tr("ROBOT_IRP6OT_M") << tr("ROBOT_IRP6P_M") << tr("ROBOT_FESTIVAL")
            << tr("ROBOT_CONVEYOR") << tr(" ROBOT_SPEAKER") << tr("ROBOT_IRP6_MECHATRONIKA") << tr("ROBOT_ELECTRON")
            << tr("ROBOT_HAND") << tr("ROBOT_SPEECHRECOGNITION");


    QLabel *FirstSetLabel = new QLabel(tr("Robot:"));
    emptyGenLayout->addWidget(FirstSetLabel);


    RobotCombo = new QComboBox(this);
    RobotCombo->setFixedWidth(200);
    RobotCombo->addItems(items);
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

    QStringList items;
    items << tr("ROBOT_UNDEFINED") << tr("ROBOT_IRP6OT_M") << tr("ROBOT_IRP6P_M") << tr("ROBOT_FESTIVAL")
            << tr("ROBOT_CONVEYOR") << tr(" ROBOT_SPEAKER") << tr("ROBOT_IRP6_MECHATRONIKA") << tr("ROBOT_ELECTRON")
            << tr("ROBOT_HAND") << tr("ROBOT_SPEECHRECOGNITION");

    //buttons add+remove

    QLabel *FirstSetLabel = new QLabel(tr("First Set:/nxxx"));
    stopGenLayout->addWidget(FirstSetLabel);
    //labels with setText

    FirstRobotCombo = new QComboBox(this);
    FirstRobotCombo->setFixedWidth(200);
    FirstRobotCombo->addItems(items);
    stopGenLayout->addWidget(FirstRobotCombo);

    QHBoxLayout * firstButtonsLayout = new QHBoxLayout;
    QPushButton * addFirstButton = new QPushButton("Add");
    QPushButton * removeFirstButton = new QPushButton("Remove");
    firstButtonsLayout->addWidget(addFirstButton);
    firstButtonsLayout->addWidget(removeFirstButton);
    stopGenLayout->addLayout(firstButtonsLayout);


    /*QLabel *SecondSetLabel = new QLabel("Second Set:");
    stopGenLayout->addWidget(SecondSetLabel);

    SecondRobotCombo = new QComboBox(this);
    SecondRobotCombo->setFixedWidth(200);
    SecondRobotCombo->addItems(items);
    stopGenLayout->addWidget(FirstRobotCombo);
    QHBoxLayout * secondButtonsLayout = new QHBoxLayout;
    QPushButton * addSecondButton = new QPushButton("Add");
    QPushButton * removeSecondButton = new QPushButton("Remove");
    secondButtonsLayout->addWidget(addSecondButton);
    secondButtonsLayout->addWidget(removeSecondButton);
    stopGenLayout->addLayout(secondButtonsLayout);*/

     setLayout(stopGenLayout);
}

//***************   SENSOR_INI_GEN   ***************//

iniSensorWidget::iniSensorWidget(QWidget * parent)
    :QWidget(parent)
{
    QVBoxLayout * iniSensorLayout = new QVBoxLayout;

    QStringList items;
    items << tr("SENSOR_CAMERA_ON_TRACK, SENSOR_CAMERA_SA");

    //buttons add+remove

    QLabel *FirstSetLabel = new QLabel(tr("Sensor:"));
    iniSensorLayout->addWidget(FirstSetLabel);


    SensorCombo = new QComboBox(this);
    SensorCombo->setFixedWidth(200);
    SensorCombo->addItems(items);
    iniSensorLayout->addWidget(SensorCombo);


     setLayout(iniSensorLayout);
}

getSensorWidget::getSensorWidget(QWidget * parent)
    :QWidget(parent)
{
    QVBoxLayout * getSensorLayout = new QVBoxLayout;

    QStringList items;
    items << tr("SENSOR_CAMERA_ON_TRACK, SENSOR_CAMERA_SA");

    //buttons add+remove

    QLabel *FirstSetLabel = new QLabel(tr("Sensor:"));
    getSensorLayout->addWidget(FirstSetLabel);


    SensorCombo = new QComboBox(this);
    SensorCombo->setFixedWidth(200);
    SensorCombo->addItems(items);
    getSensorLayout->addWidget(SensorCombo);


     setLayout(getSensorLayout);
}

