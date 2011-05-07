
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
    StateWidget(QWidget * w,Model * newmod );

    void refreshData();
    void StateSelected(BaseState *);
private:
    bool StateNameOK();
    Model * mod;

    BaseState * edited;

    QVBoxLayout *topLayout;
    QVBoxLayout *StateLayout;
    QVBoxLayout *mainLayout;

    QVBoxLayout *StateTypeLayout;
    QVBoxLayout *RunGenTypeLayout;

    QLabel *nameLabel;
    QLineEdit *stateNameEdit;
    QLabel *paramLabel;
    QLineEdit *paramEdit;

    QPushButton *OKButton;
    QPushButton *InsertButton;
    QPushButton *createTaskButton;

    QLineEdit * taskNameEdit;

    QComboBox *stateTypeCombo;
    QComboBox *subtaskCombo;


    MyTypeWidget* StateWidgets[STATE_TYPES_NUMBER];

    int tmpWidget;

signals:
    void SubtaskInserted(QString newSubtaskName);
    void InsertState(BaseState * newState);
    void selectedSubtaskName(QString newString);
    void reportError(QString msgString);



private slots:

    void forwardError(QString msgString){emit reportError(msgString);}
    void setStateSubclass(int chosen);
    void createNewSubtask();
    void SubtaskIndexChanged(QString);

    void lengthSubtaskChanged(QString newString);
    void lengthChanged(QString text);

    void AcceptState();
    void InsertState();


};

#endif // STATEWIDGET_H
