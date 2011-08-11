class EditWidget;

#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include "respecta.h"
#include "States.h"
#include "globals.h"

#include "stateWidget.h"
#include "transWidget.h"
#include "subtaskWidget.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QGridLayout;
class QVBoxLayout;
class QStackedWidget;
QT_END_NAMESPACE


/**
*   Class containing edit widgets.
*/
class EditWidget : public QStackedWidget//QTabWidget
{
    Q_OBJECT

public:
    EditWidget(RESpecTa *parent, Model * mod);

signals:
    /**
    *   Signal to the main window reporting error.
    *   @param msgString Error to display
    */
    void reportError(QString msgString);

private slots:
    void EditTasks();

    /**
    *   Calls refresh function to all widgets.
    */
    void refreshAllWidgets();
    /**
    *   Passes the selected item to the corresponding edit widget.
    *   @param item Item to pass
    */
    void itemSelected(QGraphicsItem * item);
    /**
    *   Refreshes given widget.
    *   @param index Index of the tab to be refreshed.
    */
    void refreshWidget(int index);
    /**
    *   By this slot the inside widgets communicate errors to the main window.
    */
    void forwardError(QString msgString){emit reportError(msgString);}
    /**
    *   Signals the edit widgets to cancel the Edit option(usually because a deletion occured on the scene).
    */
    void SignalDeleted();

private:
    /**
    *   Widget, which allows to edit and create transitions.
    */
    TransWidget * transWidget;
    /**
    *   Widget, which allows to edit and create states.
    */
    StateWidget * stateWidget;
    /**
    *   Widget, which allows to edit, delete and create states.
    */
    SubtaskWidget * subtaskWidget;
};
#endif // EDITWIDGET_H
