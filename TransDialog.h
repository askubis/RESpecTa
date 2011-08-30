class TransDialog;

#ifndef TRANSDIALOG_H
#define TRANSDIALOG_H
#include "globals.h"
#include <QtGui>
#include "baseState.h"
#include "Model.h"

QT_BEGIN_NAMESPACE
class QDialog;
QT_END_NAMESPACE

/**
*   DialogBox allowing to change order of transitions for a state.
*/
class TransDialog:public QDialog
{
    Q_OBJECT

public:
    /**
    *   Constructor creating the widget and all it's elements.
    */
    TransDialog(QWidget * parent, Model * mod);
    /**
    *   Destructor for this widget.
    */
    ~TransDialog(){}
    /**
    *   Opens the dialogbox for a state loading it's transitions from the model.
    */
    void openForAState(BaseState * tmp);

signals:
    /**
    *   Signals that a transition should be selected.
    */
    void TransitionSelected(Transition * tr);

    /**
    *   reports to parent widget, that an error has occured.
    */
    void reportError(QString);

private slots:
    /**
    *   Slot reacting on doubleclick on a transition on the list.
    */
    void TransSelected(QModelIndex);


    /**
    *   Moves the selected transition one position up.
    */
    void UpPressed();
    /**
    *   Moves the selected transition one position down.
    */
    void DownPressed();
    /**
    *   Close the dialogbox.
    */
    void OKPressed();
    /**
    *   Highlights all lists on the same index.
    */
    void RowChanged(int);

private:
    /**
    *   State, for which the dialog is opened.
    */
    BaseState * state;
    /**
    *   Model of the project.
    */
    Model * mod;
    /**
    *   List of conditions of the transitions.
    */
    QListWidget * transCondList;
    /**
    *   List of targets of the transitions.
    */
    QListWidget * transTargList;
    /**
    *   List of subtasks of the transitions.
    */
    QListWidget * transSubList;
};


#endif // TRANSDIALOG_H
