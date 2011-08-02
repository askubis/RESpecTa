class SubtaskWidget;

#ifndef SUBTASKWIDGET_H
#define SUBTASKWIDGET_H

#include <QLineEdit>
#include <QWidget>
#include "Model.h"


QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

/**
*   Widget responsible for editing, creating and deleting tasks.
*/
class SubtaskWidget : public QWidget
{
    Q_OBJECT
public:
    SubtaskWidget(QWidget * parent, Model * mod);
    /**
    *   Downloads list of tasks from the model.
    */
    void refreshData();

signals:
    /**
    *   Signals that a new task should be added.
    */
    void added(QString);
    /**
    *   Signals, that the selected task should be removed.
    */
    void removed(QString);
    /**
    *   Signals, that a name should be changed
    */
    void changed(QString oldName, QString newName);
    /**
    *   Signals to parent Widget, that an error has occured.
    */
    void reportError(QString);

private slots:
    /**
    *   Slot after clicking Add button, signals with added SIGNAL.
    */
    void AddClicked();
    /**
    *   Slot after clicking Change Name button, signals with changed SIGNAL.
    */
    void ChangeClicked();
    /**
    *   Slot after clicking Delete button, signals with removed SIGNAL.
    */
    void DeleteClicked();
    /**
    *   Disables or enables Add/Change buttons depending on newString.size().
    */
    void LengthChanged(QString newString);

private:
    /**
    *   Pointer to the model representing the project.
    */
    Model * model;
    /**
    *   List of subtasks in the project.
    */
    QListWidget * subtaskList;
    /**
    *   Line allowing to create new name for task.
    */
    QLineEdit * nameEdit;
    /**
    *   Button allowing to change name of a subtask.
    */
    QPushButton * changeNameButton;
    /**
    *   Button allowing to add new subtask to the project.
    */
    QPushButton * AddButton;
};

#endif // SUBTASKWIDGET_H
