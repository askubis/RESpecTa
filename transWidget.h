
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
private:
    Model * mod;

    QVBoxLayout *TransitionLayout;

    //QLabel *transCondLabel;
    QLineEdit *conditionLineEdit;


    //QWidget *extension;

    QPushButton *OKButton;
    QPushButton *InsertButton;


    Transition * edited;

    QComboBox *stateCombo;
    //QComboBox *destCombo;
    QComboBox *subtaskCombo;

    QLabel * sourceNameLabel;
    QLabel * destNameLabel;




signals:
    void insertTransition(std::pair<QString,QString>);
    void reportError(QString);

   // QStringList getSubtasksList();

private slots:

    void subtaskChanged(QString);
    void lengthChanged(QString newString);
    void AcceptTrans();
    void InsertTrans();
    void SubtaskInserted(QString);

};

#endif // TRANSWIDGET_H
