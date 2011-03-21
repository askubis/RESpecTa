#include "respecta.h"
#include "States.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE


#ifndef STATEEDITDIALOG_H
#define STATEEDITDIALOG_H
class StateEditDialog : public QDialog
{
    Q_OBJECT

public:
    StateEditDialog(QWidget *parent = 0);

private:
    QLabel *nameLabel;
    QLineEdit *stateName;
    QPushButton *typeAcceptedButton;
    QComboBox *genTypeCombo;
    //QWidget *extension;

private slots:
    void typeAccepted();

};
#endif // STATEEDITDIALOG_H
