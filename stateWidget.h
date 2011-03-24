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
class QGridLayout;
class QVBoxLayout;
QT_END_NAMESPACE

#ifndef STATEWIDGET_H
#define STATEWIDGET_H

class StateWidget : public QWidget
{
    Q_OBJECT
public:
    StateWidget(QWidget * w);
private:
    QVBoxLayout *topLayout;
    QVBoxLayout *StateLayout;

    QVBoxLayout *StateTypeLayout;
    QVBoxLayout *RunGenTypeLayout;

    QLabel *nameLabel;
    QLineEdit *stateNameEdit;

    QGridLayout *mainLayout;

    QPushButton *OKButton;
    QPushButton *InsertButton;

    QComboBox *genTypeCombo;

private slots:
    void setStateSubclass(int chosen);
    void lengthChanged(QString text);
    void AcceptState();
    void InsertState();


};

#endif // STATEWIDGET_H
