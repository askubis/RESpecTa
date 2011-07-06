class EditWidget;

#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include "respecta.h"
#include "States.h"
#include "globals.h"

#include "stateWidget.h"
#include "transWidget.h"

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
QT_END_NAMESPACE


/**
*   Class containing edit widgets.
*/
class EditWidget : public QWidget
{
    Q_OBJECT

public:
    EditWidget(QWidget *parent, Model * mod);

private:
    /**
    *   Tabwidget, which contains all the edit widgets.
    */
    QTabWidget * tabWidget;
    /**
    *   Widget, which allows to edit ad create transitions.
    */
    TransWidget * transWidget;
    /**
    *   Widget, which allows to edit ad create states.
    */
    StateWidget * stateWidget;
signals:
    /**
    *   Signal to the main window reporting error.
    *   @param msgString Error to display
    */
    void reportError(QString msgString);
private slots:
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

};
#endif // EDITWIDGET_H
