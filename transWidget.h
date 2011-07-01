
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

class TransWidget : public QWidget
{
    Q_OBJECT
public:
    TransWidget(QWidget *parent,Model * newmod );

    void refreshData();
    void TransSelected(Transition *);

    void setOKButtonDisabled(){OKButton->setDisabled(true);edited=NULL;}
private:
    Model * mod;

    QVBoxLayout *TransitionLayout;

    QLineEdit *conditionLineEdit;

    QPushButton *OKButton;
    QPushButton *InsertButton;

    Transition * edited;

    QComboBox *stateCombo;
    QComboBox *subtaskCombo;

    QLabel * sourceNameLabel;
    QLabel * destNameLabel;
signals:
    void insertTransition(std::pair<QString,QString>);
    void reportError(QString);

private slots:
    void subtaskChanged(QString);
    void lengthChanged(QString newString);
    void AcceptTrans();
    void InsertTrans();
};

#endif // TRANSWIDGET_H
