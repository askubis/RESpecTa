
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
    TransWidget(QWidget *parent);

    void refreshData();
private:
    QVBoxLayout *TransitionLayout;

    //QLabel *transCondLabel;
    QLineEdit *conditionLineEdit;


    //QWidget *extension;

    QPushButton *OKButton;
    QPushButton *InsertButton;


    QComboBox *sourceCombo;
    QComboBox *destCombo;
    QComboBox *subtaskCombo;







private slots:
    void lengthChanged(QString newString);
    void AcceptTrans();
    void InsertTrans();

};

#endif // TRANSWIDGET_H
