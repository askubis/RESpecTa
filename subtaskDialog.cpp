#include "subtaskDialog.h"


SubtaskDialog::SubtaskDialog(QWidget * parent,Model * mod): QDialog(parent)
{
    model = mod;

    setWindowTitle(tr("SubtasksDialog"));
    QGridLayout * mainLayout = new QGridLayout;

    subtaskList = new QListWidget();
    mainLayout->addWidget(subtaskList,0,0,6,2);


   QLabel * Name = new QLabel ("Name");
   mainLayout->addWidget(Name, 6,0, 1, 2);

   changeNameButton = new QPushButton("Change Name");
   connect(changeNameButton, SIGNAL(clicked()), this, SLOT(ChangeClicked()));
   mainLayout->addWidget(changeNameButton, 8,0);

   QPushButton * DeleteButton = new QPushButton("Delete");
   connect(DeleteButton, SIGNAL(clicked()), this, SLOT(DeleteClicked()));
   mainLayout->addWidget(DeleteButton, 8,1);

   AddButton = new QPushButton("Add");
   connect(AddButton, SIGNAL(clicked()), this, SLOT(AddClicked()));
   mainLayout->addWidget(AddButton, 9,0);

   QPushButton * OKButton = new QPushButton("OK");
   connect(OKButton, SIGNAL(clicked()), this, SLOT(OKPressed()));
   mainLayout->addWidget(OKButton, 9,1);

   nameEdit = new QLineEdit();
   mainLayout->addWidget(nameEdit, 7,0, 1, 2);
   connect(nameEdit, SIGNAL(textChanged(QString)), this, SLOT(LengthChanged(QString)));

   changeNameButton->setDisabled(true);
   AddButton->setDisabled(true);



    setLayout(mainLayout);
}

void SubtaskDialog::reloadName()
{
    subtaskList->clear();
    subtaskList->addItems(model->getTasksNameLists());
    subtaskList->setCurrentRow(0);
}

void SubtaskDialog::ChangeClicked()
{
    if((subtaskList->findItems(nameEdit->text(),Qt::MatchExactly)).size()!=0)
    {
        emit reportError(QString("This subtask name is already taken"));
        return;
    }
    QStringList list = model->getTasksNameLists();
    if(list[subtaskList->currentIndex().row()]!= nameEdit->text())
    {
        model->changeSubtaskName(list[subtaskList->currentIndex().row()], nameEdit->text());
        emit changed(list[subtaskList->currentIndex().row()], nameEdit->text());
        reloadName();
    }
}

void SubtaskDialog::AddClicked()
{
    if(model->checkSubtaskExists(nameEdit->text()))
    {
        emit reportError(QString("Subtask with that name already exists"));
        return;
    }
    else
    {
        model->addSubtask(nameEdit->text());
        emit added(nameEdit->text());
        reloadName();
    }
}

void SubtaskDialog::DeleteClicked()
{
    QStringList list = model->getTasksNameLists();
    model->DeleteSubtask(list[subtaskList->currentIndex().row()]);
    emit removed(list[subtaskList->currentIndex().row()]);
    reloadName();

}

void SubtaskDialog::LengthChanged(QString newString)
{
    if(newString.size()>0)
    {        changeNameButton->setDisabled(false);
             AddButton->setDisabled(false);
    }
    else
    {        changeNameButton->setDisabled(true);
             AddButton->setDisabled(true);
    }
}

void SubtaskDialog::OKPressed()
{
    this->setVisible(false);
}
