#ifndef STATETYPEWIDGETS_H
#define STATETYPEWIDGETS_H

#include "respecta.h"
#include "States.h"
#include "globals.h"

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
    QLineEdit * argsLineEdit;
    QLineEdit * speechLineEdit;
    QLabel * speechLabel;
    QLabel * argsLabel;
private slots:
    void addPoses();
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
    stopGenWidget(QWidget * parent);
private:

    QComboBox * FirstRobotCombo;
    QComboBox * SecondRobotCombo;

private slots:

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



#endif // STATETYPEWIDGETS_H
