class TransWidget;

#ifndef TRANSWIDGET_H
#define TRANSWIDGET_H


#include "respecta.h"
#include "States.h"
#include "globals.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class QGridLayout;
class QVBoxLayout;
QT_END_NAMESPACE

/**
*   a Widget, which allows to edit and create Transitions.
*/
class TransWidget : public QWidget
{
    Q_OBJECT
public:
    TransWidget(QWidget *parent,Model * newmod );

    /**
    *   Refreshes data, especially the subtasks list.
    */
    void refreshData();
    /**
    *   Loads data of a Transition to edit.
    */
    void TransSelected(Transition *);

    /**
    *   Disables OK button (used when condition.size()==0).
    */
    void setOKButtonDisabled(){OKButton->setDisabled(true);edited=NULL;}
private:
    /**
    *   Model of the project.
    */
    Model * mod;

    /**
    *   Lineedit allowing to enter/edit condition of the transition.
    */
    QLineEdit *conditionLineEdit;

    /**
    *   Button which signals that the user accepts changes made in the Transition.
    */
    QPushButton *OKButton;
    /**
    *   Button which signals, that the user wants to add this transition to the project.
    */
    //QPushButton *InsertButton;

    /**
    *   Transition, which is currently being edited.
    */
    Transition * edited;

    /**
    *   Combobox allowing to choose a state in a subtask, which will be the start of subtsk execution.
    */
    QComboBox *stateCombo;
    /**
    *   Combobox allowing to choose a subtask, which will be executed from the state chosen in stateCombo.
    */
    QComboBox *subtaskCombo;


    QComboBox * sourceNameCombo;

    QComboBox * destNameCombo;
signals:
    /**
    *   Signals,that a transition will be inserted, gibving it's attributes.
    */
    //void insertTransition(std::pair<QString,QString>);
    /**
    *   Reports to the parent widget, that an error has occured.
    */
    void reportError(QString);

private slots:
    /**
    *   Refreshes State list in StateCombo after a change in subtaskCombo.
    */
    void subtaskChanged(QString);
    /**
    *   Enables/Disables ok/insert buttons when a change has been made in the condition.
    */
    void lengthChanged(QString newString);
    /**
    *   Changes the edited transition.
    */
    void AcceptTrans();
    /**
    *   Signals with the insertTransition Signal, that the user wants to insert a transition into the project.
    */
    //void InsertTrans();
};

#endif // TRANSWIDGET_H
