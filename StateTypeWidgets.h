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


class sysIniWidget : public QWidget
{
    Q_OBJECT
public:
    sysIniWidget(QWidget * parent);
private slots:
    void createECPSection();
    void createMPSection();
};

class runGenWidget : public QWidget
{
    Q_OBJECT
public:
    runGenWidget(QWidget * parent);
private:
    QComboBox * genTypeCombo;
    QComboBox * robotCombo;
    QLineEdit * argsLineEdit;
    QLineEdit * speechLineEdit;
    QLabel * speechLabel;
    QLabel * argsLabel;
    QListWidget * PoseList;
    //
    QLineEdit * trjFileName;
    PoseDialog * poseDialog;
private slots:
    void PoseCancel();
    void PosesReset();
    void PoseAdd();
    void showAddPosesDialog();
    void selectTrjFilePath();

};

class emptyGenForSetWidget : public QWidget
{
    Q_OBJECT
public:
    emptyGenForSetWidget(QWidget * parent);
private:

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

class emptyGenWidget : public QWidget
{
    Q_OBJECT
public:
    emptyGenWidget(QWidget * parent);
private:
    EmptyGenState * State;
    QComboBox * RobotCombo;


private slots:

};

class waitStateWidget : public QWidget
{
    Q_OBJECT
public:
    waitStateWidget(QWidget * parent);
private:
    QLineEdit * timeSpan;


private slots:

};

class stopGenWidget : public QWidget
{
    Q_OBJECT
public:
    QListWidget * FirstRobotList;
    stopGenWidget(QWidget * parent);
private:

    QComboBox * FirstRobotCombo;

private slots:
    void addFirst();
    void removeFirst();
};

class iniSensorWidget : public QWidget
{
    Q_OBJECT
public:
    iniSensorWidget(QWidget * parent);
private:

    QComboBox * SensorCombo;

private slots:

};


class getSensorWidget : public QWidget
{
    Q_OBJECT
public:
    getSensorWidget(QWidget * parent);
private:

    QComboBox * SensorCombo;

private slots:

};






class PoseDialog:public QDialog
{
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


#endif // STATETYPEWIDGETS_H
