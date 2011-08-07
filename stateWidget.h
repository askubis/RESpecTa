class StateWidget;

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

/**
*   Widget allowing to edit states, containing widgets for all child-classes of BaseState.
*/
class StateWidget : public QWidget
{
    Q_OBJECT
public:
    StateWidget(QWidget * w,Model * newmod );

    /**
    *   Created for future needs, does nothing.
    */
    void refreshData();
    /**
    *   opens a MyTypeWidget connected to the state of ToLoadState, and loads all the data of ToLoadState to relevant fields.
    */
    void StateSelected(BaseState * ToLoadState);

    /**
    *   Disables OK button and notes, that no state is currently edited.
    */
    void setOKButtonDisabled(){OKButton->setDisabled(true);edited=NULL;}

signals:
    /**
    *   Signals, that newState will be inserted.
    */
    //void InsertState(BaseState * newState);
    /**
    *   Signals to a parent widget, that an error has occured.
    */
    void reportError(QString msgString);
    /**
    *   Signals, that user requests to change oldState to newState.
    */
    void ReplaceState(BaseState * oldState, BaseState * newState);

private slots:
    /**
    *   Forwards error message from child widgets to aprent widget.
    */
    void forwardError(QString msgString){emit reportError(msgString);}
    /**
    *   Changes active widget to that of Type == chosen, and blocks/unblocks NameLineEdit if neccessary.
    */
    void setStateSubclass(int chosen);
    /**
    *   Blocks or unblocks ok/insert buttons depending on text.size().
    */
    void lengthChanged(QString text);

    /**
    *   User accepts change in state (uses ReplaceState signal).
    */
    void AcceptState();
    /**
    *   User wants to insert a State (uses InsertState Signal)
    */
    //void InsertState();

private:
    /**
    *   Checks if name specified for the state is OK.
    *   @returns True, if anme is correct.
    */
    bool StateNameOK();
    /**
    *   Pointer to the model of the project.
    */
    Model * mod;

    /**
    *   State that is currently edited, NULL if none.
    */
    BaseState * edited;

    /**
    *   Layout containing base informations for all states.
    */
    QVBoxLayout *StateLayout;
    /**
    *   Layout containing other layouts and all the MyWidgetType widgets.
    */
    QVBoxLayout *mainLayout;

    /**
    *   LineEdit to edit Name of the state.
    */
    QLineEdit *stateNameEdit;
    /**
    *   LineEdit to edit parameters of a state.
    */
    QLineEdit *paramEdit;

    /**
    *   Button accepting change of edited state.
    */
    QPushButton *OKButton;
    /**
    *   Button signaling that this state will be inserted.
    */
    //QPushButton *InsertButton;

    /**
    *   Combobox to choose a type of the state.
    */
    QComboBox *stateTypeCombo;

    /**
    *   Widgets allowing to edit different types of states.
    */
    MyTypeWidget* StateWidgets[STATE_TYPES_NUMBER];
    /**
    *   Index of the widget, which is currently active.
    */
    int tmpWidget;
};

#endif // STATEWIDGET_H
