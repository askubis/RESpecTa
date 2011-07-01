#ifndef TRANSDIALOG_H
#define TRANSDIALOG_H
class TransDialog;
#include "globals.h"
#include <QtGui>
#include "baseState.h"
#include "Model.h"
class TransDialog:public QDialog
{
    Q_OBJECT

public:
    TransDialog(QWidget * parent, Model * mod);
    ~TransDialog(){}
    void openForAState(BaseState * tmp);

signals:
    void reportError(QString);

private slots:
    void UpPressed();
    void DownPressed();
    void OKPressed();
    void RowChanged(int);

private:
    BaseState * state;
    Model * mod;
    QListWidget * transCondList;
    QListWidget * transTargList;
    QListWidget * transSubList;
};


#endif // TRANSDIALOG_H
