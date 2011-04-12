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

#ifndef EDITWIDGET_H
#define EDITWIDGET_H



class EditWidget : public QWidget
{
    Q_OBJECT

public:
    EditWidget(QWidget *parent = 0);

private:
    QTabWidget * tabWidget;
    TransWidget * transWidget;
    StateWidget * stateWidget;
signals:
    void reportError(QString msgString);
private slots:
    void refreshWidget(int);
    void forwardError(QString msgString){emit reportError(msgString);}




};
#endif // EDITWIDGET_H
