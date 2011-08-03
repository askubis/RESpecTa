#include "subtaskWidget.h"


SubtaskWidget::SubtaskWidget(QWidget * parent,Model * mod): QWidget(parent)
{
    model = mod;

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

   QPushButton * CleanButton = new QPushButton("Clean");
   connect(CleanButton, SIGNAL(clicked()), this, SLOT(CleanClicked()));
   mainLayout->addWidget(CleanButton, 9, 1);

   nameEdit = new QLineEdit();
   nameEdit->setValidator(new QRegExpValidator(QRegExp("^[\\w\\s\\-]*$"), nameEdit));
   mainLayout->addWidget(nameEdit, 7,0, 1, 2);
   connect(nameEdit, SIGNAL(textChanged(QString)), this, SLOT(LengthChanged(QString)));

   changeNameButton->setDisabled(true);
   AddButton->setDisabled(true);

    setLayout(mainLayout);
}

void SubtaskWidget::CleanClicked()
{
    QStringList list = model->getTasksNameLists();
    model->CleanTask(list[subtaskList->currentIndex().row()]);
}

void SubtaskWidget::refreshData()
{
    subtaskList->clear();
    subtaskList->addItems(model->getTasksNameLists());
    subtaskList->setCurrentRow(0);
}

void SubtaskWidget::ChangeClicked()
{
    if((subtaskList->findItems(nameEdit->text(),Qt::MatchExactly)).size()!=0)
    {
        emit reportError(QString("This subtask name is already taken"));
        return;
    }
    QStringList list = model->getTasksNameLists();
    if(list[subtaskList->currentIndex().row()]!= nameEdit->text())
    {
        emit changed(list[subtaskList->currentIndex().row()], nameEdit->text());
        refreshData();
    }
}

void SubtaskWidget::AddClicked()
{
    if(model->checkSubtaskExists(nameEdit->text()))
    {
        emit reportError(QString("Subtask with that name already exists"));
        return;
    }
    else
    {
        emit added(nameEdit->text());
        refreshData();
    }
}

void SubtaskWidget::DeleteClicked()
{
    QStringList list = model->getTasksNameLists();
    emit removed(list[subtaskList->currentIndex().row()]);
    refreshData();
}

void SubtaskWidget::LengthChanged(QString newString)
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

