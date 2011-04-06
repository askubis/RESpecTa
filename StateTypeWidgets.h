#ifndef STATETYPEWIDGETS_H
#define STATETYPEWIDGETS_H

#include "respecta.h"
#include "States.h"
#include "globals.h"
#include "Pose.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QGridLayout;
class QVBoxLayout;
class QListWidget;
class QListItemWidget;
QT_END_NAMESPACE
class PoseDialog;
class ECPDialog;
class MPDialog;




class MyTypeWidget : public QWidget
{
   Q_OBJECT
public:
    MyTypeWidget(QWidget * parent):QWidget(parent){}
    virtual BaseState * getStateObject() = 0;
private:

private slots:

};

class sysIniWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    sysIniWidget(QWidget * parent);
    BaseState * getStateObject();

    sysInitState * getState(){return State;}
    void setState(sysInitState * newState){State = newState;}
    QListWidget * robotsInitialized;
private:
    sysInitState * State;

    ECPDialog * ecpDialog;
    MPDialog * mpDialog;
private slots:
    void removeECPSection();
    void createECPSection();
    void changeMPSection();
};

class runGenWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    runGenWidget(QWidget * parent);
    BaseState * getStateObject();

    RunGenState * getState(){return State;}
    void setState(RunGenState * newState){State = newState;}
private:
    RunGenState * State;

    QComboBox * genTypeCombo;
    QComboBox * robotCombo;
    QLineEdit * argsLineEdit;
    QLineEdit * speechLineEdit;
    QLabel * speechLabel;
    QLabel * argsLabel;
    QListWidget * PoseList;
    QLineEdit * trjFileName;
    PoseDialog * poseDialog;
private slots:
    void showAddPosesDialog();
    void selectTrjFilePath();
};

class emptyGenForSetWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    emptyGenForSetWidget(QWidget * parent);
    BaseState * getStateObject();

    EmptyGenForSetState * getState(){return State;}
    void setState(EmptyGenForSetState * newState){State = newState;}
private:
    EmptyGenForSetState * State;

    QListWidget * FirstRobotList;
    QListWidget * SecondRobotList;
    QComboBox * FirstRobotCombo;
    QComboBox * SecondRobotCombo;
private slots:
    void addFirst();
    void removeFirst();
    void addSecond();
    void removeSecond();
};

class emptyGenWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    emptyGenWidget(QWidget * parent);
    BaseState * getStateObject();

    EmptyGenState * getState(){return State;}
    void setState(EmptyGenState * newState){State = newState;}
private:
    EmptyGenState * State;

    QComboBox * RobotCombo;
private slots:

};

class waitStateWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    waitStateWidget(QWidget * parent);
    BaseState * getStateObject();

    WaitState * getState(){return State;}
    void setState(WaitState * newState){State = newState;}
private:
    WaitState * State;

    QLineEdit * timeSpan;
private slots:

};

class stopGenWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    stopGenWidget(QWidget * parent);
    BaseState * getStateObject();

    StopGenState * getState(){return State;}
    void setState(StopGenState * newState){State = newState;}
private:
    StopGenState * State;

    QListWidget * RobotList;
    QComboBox * RobotCombo;
private slots:
    void add();
    void remove();
};

class iniSensorWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    iniSensorWidget(QWidget * parent);
    BaseState * getStateObject();

    InitiateSensorState * getState(){return State;}
    void setState(InitiateSensorState * newState){State = newState;}
private:
    InitiateSensorState * State;

    QComboBox * SensorCombo;
private slots:

};


class getSensorWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    getSensorWidget(QWidget * parent);
    BaseState * getStateObject();

    GetSensorState * getState(){return State;}
    void setState(GetSensorState * newState){State = newState;}
private:
    GetSensorState * State;

    QComboBox * SensorCombo;
private slots:

};



//***********************************************   DIALOGS   ***********************************************//



class PoseDialog:public QDialog
{
    Q_OBJECT
public:
    PoseDialog(QWidget * parent);

    Coordinates * getCoords(){return coords;}
    void setCoords(Coordinates * newCoords){coords = newCoords;}
private:
    QListWidget * poseList;
    QComboBox * motionTypeCombo;
    QComboBox * coordTypeCombo;
    std::vector<QLineEdit *> coordEdit;
    std::vector<QLineEdit *> velEdit;
    std::vector<QLineEdit *> accEdit;

    Coordinates * coords;
private slots:
    void AddPose();
    void RemovePose();
    void PoseOK();
    void PoseCancel();
    void PosesReset();

};

class ECPDialog:public QDialog
{
    Q_OBJECT
public:
    ECPDialog(QWidget * parent);
private:
    QListWidget * genList;
    QComboBox * genTypeCombo;
    QLineEdit * argLineEdit;
    QComboBox * robotCombo;
    genInit genInitObj;
    sysIniWidget * parentx;
    sysInitState * tmpState;

private slots:
    void remove();
    void add();
    void OKPressed();
    void CancelPressed();

};

class MPDialog:public QDialog
{
    Q_OBJECT
public:
    MPDialog(QWidget * parent);
private:
    QListWidget * sensorList;
    QComboBox * sensorCombo;
    QComboBox * transmitterCombo;

private slots:
    void remove();
    void add();
    void OKPressed();
    void CancelPressed();

};


#endif // STATETYPEWIDGETS_H
