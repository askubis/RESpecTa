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
private:
    sysInitState * State;

    QListWidget * robotsInitialized;
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
    void PoseCancel();
    void PosesReset();
    void PoseAdd();
    void showAddPosesDialog();
    void selectTrjFilePath();
};

class emptyGenForSetWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    emptyGenForSetWidget(QWidget * parent);
    BaseState * getStateObject();
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
private:
    QListWidget * poseList;
    QComboBox * motionTypeCombo;
    QComboBox * coordTypeCombo;
    std::vector<QLineEdit *> coordEdit;
    std::vector<QLineEdit *> velEdit;
    std::vector<QLineEdit *> accEdit;
private slots:

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

private slots:
    void remove();
    void add();

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

};


#endif // STATETYPEWIDGETS_H
