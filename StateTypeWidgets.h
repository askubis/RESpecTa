class MyTypeWidget;
class sysIniWidget;
class runGenWidget;
class stopGenWidget;
class iniSensorWidget;
class getSensorWidget;
class emptyGenForSetWidget;
class emptyGenWidget;
class waitStateWidget;
class CoordDialog;
class MPDialog;
class ECPDialog;

#ifndef STATETYPEWIDGETS_H
#define STATETYPEWIDGETS_H

#include "respecta.h"
#include "States.h"
#include "globals.h"
#include "Pose.h"
#include "stateWidget.h"

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
class QWidget;
QT_END_NAMESPACE

/**
*   Base class to all widgets, which allow editing different state types.
*/
class MyTypeWidget : public QWidget
{
   Q_OBJECT
public:
    MyTypeWidget(QWidget * parent,Model * newmod ):QWidget(parent){mod = newmod;}
    /**
    *   Function returning object of the class, which is represented by the child-class of this class.
    */
    virtual BaseState * getStateObject() = 0;
    /**
    *   Function opening state State(of a child-class of BaseState) for edition in the widget.
    */
    virtual void setState(BaseState * State) = 0;
private:
    Model * mod;
};

/**
*   Widget allowing to edit sysInitState.
*/
class sysIniWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    sysIniWidget(QWidget * parent,Model * newmod );
    BaseState * getStateObject();

    void setState(BaseState * state);

signals:
    /**
    *   Signal to parent, that an error has ocured.
    */
    void reportError(QString msgString);

private slots:
    /**
    *   Removes ECP section connected with the robot, which is selected in the robotsInitialized widget.
    */
    void removeECPSection();
    /**
    *   Opens ECPDialog.
    */
    void createECPSection();
    /**
    *   Opens MPDialog.
    */
    void changeMPSection();
    /**
    *   Adds new ECP section.
    *   @param newInit Robot initialization object to insert.
    */
    void InsertECP(robotInit newInit);
    /**
    *   Changes MP section.
    */
    void InsertMP (std::vector<Sensor> sensors, Transmitter trans);
    /**
    *   Forwards errors from DialogBox using reportError signal.
    */
    void forwardError(QString msgString){emit reportError(msgString);}

private:
    /**
    *   State, which is being edited.
    */
    sysInitState * State;

    /**
    *   Widget, which lists all initialized robots.
    */
    QListWidget * robotsInitialized;

    /**
    *   A dialogbox allowing to create a new ECP section(robots).
    */
    ECPDialog * ecpDialog;
    /**
    *   A dialogbox allowing to change MP section(sensors,transmitters, etc.).
    */
    MPDialog * mpDialog;
};

/**
*   Widget allowing to edit runGenState.
*/
class runGenWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    runGenWidget(QWidget * parent,Model * newmod );
    BaseState * getStateObject();

    void setState(BaseState * state);

signals:
    /**
    *   Signal to parent, that an error has ocured.
    */
    void reportError(QString msgString);

private slots:
    /**
    *   Inserts coordinates to the state.
    *   @param newCoords Coordinates sent from the CoordsDialog to insert.
    */
    void CoordsInsert(Coordinates * newCoords);
    /**
    *   Opens CoordDialog.
    */
    void showAddPosesDialog();
    /**
    *   Opens file browse dialog allowing to choose the trajectory file.
    */
    void selectTrjFilePath();
    /**
    *   Forwards errors from DialogBox using reportError signal.
    */
    void forwardError(QString msgString){emit reportError(msgString);}

private:
    /**
    *   State to edit.
    */
    RunGenState * State;

    /**
    *   Combobox containing generatorTypes.
    */
    QComboBox * genTypeCombo;
    /**
    *   combobox containing robotTypes.
    */
    QComboBox * robotCombo;
    /**
    *   Lineedit allowing to add argument for the generator.
    */
    QLineEdit * argsLineEdit;
    /**
    *   Lineedit allowing to specify speech for the robot.
    */
    QLineEdit * speechLineEdit;
    /**
    *   Lineedit allowing to spedify path for trajectory file.
    */
    QLineEdit * trjFileName;
    /**
    *   DialogBox allowing to edit Coordiantes.
    */
    CoordDialog * coordDialog;
};

/**
*   Widget allowing to edit emptyGenForSetState.
*/
class emptyGenForSetWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    emptyGenForSetWidget(QWidget * parent,Model * newmod );
    BaseState * getStateObject();

    void setState(BaseState * state);

signals:
    /**
    *   Signal to parent, that an error has ocured.
    */
    void reportError(QString msgString);

private slots:
    /**
    *   Adds robot selected in FirstComboBox to the FirstRobotList.
    */
    void addFirst();
    /**
    *   Removes robot selected in FirstComboBox from the FirstRobotList.
    */
    void removeFirst();
    /**
    *   Adds robot selected in SecondComboBox to the SecondRobotList.
    */
    void addSecond();
    /**
    *   Removes Robot selected in SecondComboBox from SecondRobotList.
    */
    void removeSecond();

private:
    /**
    *   State, which is edited.
    */
    EmptyGenForSetState * State;

    /**
    *   List of robots in the first Set.
    */
    QListWidget * FirstRobotList;
    /**
    *   List of robots in the second Set.
    */
    QListWidget * SecondRobotList;
    /**
    *   Combobox allowing to choose Robot for the first set.
    */
    QComboBox * FirstRobotCombo;
    /**
    *   Combobox allowing to choose Robot for the second set.
    */
    QComboBox * SecondRobotCombo;
};

/**
*   Widget allowing to edit EmptyGenState.
*/
class emptyGenWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    emptyGenWidget(QWidget * parent,Model * newmod );
    BaseState * getStateObject();

    void setState(BaseState * state);

private:
    /**
    *   State, which is edited.
    */
    EmptyGenState * State;

    /**
    *   LineEdit allowing to add an argument, which will be passed to the function in MRROC++.
    */
    QLineEdit * argLineEdit;
    /**
    *   Combobox allowing to choose Robot, for which the empty generator will be stared.
    */
    QComboBox * RobotCombo;
};

/**
*   Widget allowing to edit waitState.
*/
class waitStateWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    waitStateWidget(QWidget * parent,Model * newmod );
    BaseState * getStateObject();

    void setState(BaseState * state);

private:
    /**
    *   State, which is edited.
    */
    WaitState * State;

    /**
    *   Lineedit allowing to specify time (in ms.) for which the system will be idle.
    */
    QLineEdit * timeSpan;
};

/**
*   Widget allowing to edit stopState.
*/
class stopGenWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    stopGenWidget(QWidget * parent,Model * newmod );
    BaseState * getStateObject();

    void setState(BaseState * state);

signals:
    /**
    *   Signal to parent, that an error has ocured.
    */
    void reportError(QString msgString);

private slots:
    /**
    *   Adds a robot selected in RobotCombo to RobotList.
    */
    void add();
    /**
    *   Removes a robot selected in RobotCombo from RobotList.
    */
    void remove();

private:
    /**
    *   State which is edited.
    */
    StopGenState * State;

    /**
    *   List of robots, which will be stopped.
    */
    QListWidget * RobotList;
    /**
    *   Combobox allowing to choose a robot which will be added/removed from the list.
    */
    QComboBox * RobotCombo;
};

/**
*   State allowing to edit iniSensorState.
*/
class iniSensorWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    iniSensorWidget(QWidget * parent,Model * newmod );
    BaseState * getStateObject();

    void setState(BaseState * state);

private:
    /**
    *   State, which is edited.
    */
    InitiateSensorState * State;

    /**
    *   Combobox, allowing to choose Sensor.
    */
    QComboBox * SensorCombo;
};

/**
*   Widget allowing to edit getSensorState.
*/
class getSensorWidget : public MyTypeWidget
{
    Q_OBJECT
public:
    getSensorWidget(QWidget * parent,Model * newmod );
    BaseState * getStateObject();

    void setState(BaseState * state);

private:
    /**
    *   State, which is edited.
    */
    GetSensorState * State;

    /**
    *   Combobox, allowing to choose Sensor.
    */
    QComboBox * SensorCombo;
};


//***********************************************   DIALOGS   ***********************************************//

/**
*   Dialogbox allowing to specify coordinates for runGenState.
*/
class CoordDialog:public QDialog
{
    Q_OBJECT
public:
    CoordDialog(QWidget * parent);

    Coordinates * getCoords(){return coords;}
    void setCoords(Coordinates * newCoords){coords = newCoords;}
    void coordsUpdated();

signals:
    /**
    *   Signal to RunGenWidget, that user has accepted Coordinates.
    */
    void InsertCoords(Coordinates * newCoords);
    /**
    *   Signal to parent, that an error has ocured.
    */
    void reportError(QString msgString);

private slots:
    /**
    *   Adds a pose to the list.
    */
    void AddPose();
    /**
    *   Accepts poses and exits the dialogbox.
    */
    void PoseOK();
    /**
    *   Exits without saving poses.
    */
    void PoseCancel();
    /**
    *   Resets all poses in the list.
    */
    void PosesReset();

private:
    /**
    *   Number of values in pose specification.
    */
    int num;
    /**
    *   List of poses.
    */
    QListWidget * poseList;
    /**
    *   Combobox allowing to choose between relative and absolute Pose specification.
    */
    QComboBox * motionTypeCombo;
    /**
    *   Combobox allowing to choose motion type.
    */
    QComboBox * coordTypeCombo;
    /**
    *   Lineedits to edit Coordinates.
    */
    std::vector<QLineEdit *> coordEdit;
    /**
    *   Lineedits to edit Velocities.
    */
    std::vector<QLineEdit *> velEdit;
    /**
    *   Lineedits to edit Accelerations.
    */
    std::vector<QLineEdit *> accEdit;
    /**
    *   Coordinates of the move.
    */
    Coordinates * coords;
};

/**
*   Widget allowing to create new robotInit instances for sysIniState.
*/
class ECPDialog:public QDialog
{
    Q_OBJECT
public:
    ECPDialog(QWidget * parent);

signals:
    /**
    *   Signal to parent, that a new robotInit instance has been added.
    */
    void InsertECP(robotInit newInit);
    /**
    *   Signal to parent, that an error has ocured.
    */
    void reportError(QString msgString);

private slots:
    /**
    *   Removes items selected on the genList.
    */
    void remove();
    /**
    *   Adds generator and his argument to the list.
    */
    void add();
    /**
    *   Saves data and exits dialog.
    */
    void OKPressed();
    /**
    *   Exits the dialog without saving.
    */
    void CancelPressed();

private:
    /**
    *   List of generators used for the robot, with their arguments.
    */
    QListWidget * genList;
    /**
    *   Combobox allowing to choose a generator to add.
    */
    QComboBox * genTypeCombo;
    /**
    *   Lineedit to specify argument for generator.
    */
    QLineEdit * argLineEdit;
    /**
    *   Combobox allowing to choose robot.
    */
    QComboBox * robotCombo;
    /**
    *   robotInit object, which is edited.
    */
    robotInit robotInitObj;
};

/**
*   DialogBox allowing to edit MP section of the sysIniState.
*/
class MPDialog:public QDialog
{
    Q_OBJECT
public:
    MPDialog(QWidget * parent);
    void setSensTrans(std::vector<Sensor> sens, Transmitter tran);

signals:
    /**
    *   Signals parent, that user has accepted changes.
    */
    void InsertMP (std::vector<Sensor> sensors, Transmitter trans);
    /**
    *   Signal to parent, that an error has ocured.
    */
    void reportError(QString msgString);

private slots:
    /**
    *   Removes sensor in the combobox from the list.
    */
    void remove();
    /**
    *   Removes sensor selected in the combobox from the list.
    */
    void add();
    /**
    *   Saves changes and exit the dialogbox.
    */
    void OKPressed();
    /**
    *   Exit dialogbox without saving changes.
    */
    void CancelPressed();

private:
    /**
    *   List of used sensors.
    */
    QListWidget * sensorList;
    /**
    *   Combobox allowing to choose sensors to add and remove sensors.
    */
    QComboBox * sensorCombo;
    /**
    *   Combobox allowing to choose a transmitter to initialize.
    */
    QComboBox * transmitterCombo;
};


#endif // STATETYPEWIDGETS_H
