
#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include "respecta.h"
#include "States.h"
#include "globals.h"
#include "StateTypeWidgets.h"

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
QT_END_NAMESPACE


class StateWidget : public QWidget
{
    Q_OBJECT
public:
    StateWidget(QWidget * w);
private:
    QVBoxLayout *topLayout;
    QVBoxLayout *StateLayout;
    QVBoxLayout *mainLayout;

    QVBoxLayout *StateTypeLayout;
    QVBoxLayout *RunGenTypeLayout;

    QLabel *nameLabel;
    QLineEdit *stateNameEdit;


    QPushButton *OKButton;
    QPushButton *InsertButton;
    QPushButton *createTaskButton;

    QLineEdit * taskNameEdit;

    QComboBox *stateTypeCombo;
    QComboBox *subtaskCombo;

    QWidget * sysIni;
    QWidget * runGen;
    QWidget * emptyForSet;
    QWidget * emptyGen;
    QWidget * waitGen;
    QWidget * stopGen;
    QWidget * initSensor;
    QWidget * getSensorReading;
    QWidget* StateWidgets[STATES_NUMBER];

    int tmpWidget;

private slots:
    void setStateSubclass(int chosen);

    void createNewSubtask();

    void lengthSubtaskChanged(QString newString);
    void lengthChanged(QString text);

    void AcceptState();
    void InsertState();


};

#endif // STATEWIDGET_H
