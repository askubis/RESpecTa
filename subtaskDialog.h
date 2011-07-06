class SubtaskDialog;

#ifndef SUBTASKDIALOG_H
#define SUBTASKDIALOG_H

#include <QLineEdit>
#include <QDialog>
#include "Model.h"

//TODO: change to widget

class SubtaskDialog : public QDialog
{
    Q_OBJECT
public:
    SubtaskDialog(QWidget * parent, Model * mod);
    void reloadName();

private:
    Model * model;
    QListWidget * subtaskList;
    QLineEdit * nameEdit;
    QPushButton * changeNameButton;
    QPushButton * AddButton;

signals:
    void added(QString);
    void removed(QString);
    void changed(QString, QString);
    void reportError(QString);

private slots:
    void AddClicked();
    void ChangeClicked();
    void DeleteClicked();
    void LengthChanged(QString);
    void OKPressed();
};

#endif // SUBTASKDIALOG_H
