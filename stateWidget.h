
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

    void setOKButtonDisabled(){OKButton->setDisabled(true);edited=NULL;}
private:
    bool StateNameOK();
    Model * mod;

    BaseState * edited;
    QString oldStateName;

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

    QComboBox *stateTypeCombo;

    MyTypeWidget* StateWidgets[STATE_TYPES_NUMBER];

    int tmpWidget;
signals:
    void InsertState(BaseState * newState);
    void reportError(QString msgString);
    void ReplaceState(BaseState * oldState, BaseState * newState, QString oldName);

private slots:
    void forwardError(QString msgString){emit reportError(msgString);}
    void setStateSubclass(int chosen);
    void lengthChanged(QString text);

    void AcceptState();
    void InsertState();
};

#endif // STATEWIDGET_H
