#include "transWidget.h"
#include <QtGui>
//#include "GraphFunctions.h"
//#include "GraphFunctions.cpp"




using namespace boost;

TransWidget::TransWidget(QWidget *parent,Model * newmod )
: QWidget(parent)
{
    mod = newmod;
   TransitionLayout = new QVBoxLayout;

   QLabel *transCondLabel = new QLabel(tr("Transition condition:"));
   conditionLineEdit = new QLineEdit;
   connect(conditionLineEdit, SIGNAL(textChanged(QString)), this, SLOT(lengthChanged(QString)));
   QHBoxLayout *bottomLayout = new QHBoxLayout;
   TransitionLayout->addWidget(transCondLabel);
   TransitionLayout->addWidget(conditionLineEdit);


   QLabel * taskLabel = new QLabel(tr("Subtask:"));
   subtaskCombo = new QComboBox(this);
   subtaskCombo->addItem("None");
   subtaskCombo->addItems(mod->getTasksNameListsWithoutMain());
   TransitionLayout->addWidget(taskLabel);
   TransitionLayout->addWidget(subtaskCombo);
   connect(subtaskCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(subtaskChanged(QString)));

   QLabel *stateLabel = new QLabel(tr("State:"));
   stateCombo = new QComboBox(this);
   TransitionLayout->addWidget(stateLabel);
   TransitionLayout->addWidget(stateCombo);

   OKButton = new QPushButton(tr("&OK"));
   OKButton->setChecked(false);
   connect(OKButton, SIGNAL(clicked()), this, SLOT(AcceptTrans()));
   OKButton->setDisabled(true);
   bottomLayout->addWidget(OKButton);

   InsertButton = new QPushButton(tr("&Insert"));
   InsertButton->setChecked(false);
   connect(InsertButton, SIGNAL(clicked()), this, SLOT(InsertTrans()));
   InsertButton->setDisabled(true);
   bottomLayout->addWidget(InsertButton);



   QLabel * sourceLabel =new QLabel(tr("Source state:"));
   QLabel * sourceNameLabel = new QLabel();

   QLabel * destLabel =new QLabel(tr("Destination state:"));
   QLabel * destNameLabel = new QLabel();

   TransitionLayout->addWidget(sourceLabel);
   TransitionLayout->addWidget(sourceNameLabel);
   TransitionLayout->addWidget(destLabel);
   TransitionLayout->addWidget(destNameLabel);



   TransitionLayout->addStretch();
   TransitionLayout->addLayout(bottomLayout);
   edited = NULL;
   OKButton->setDisabled(true);
   setLayout(TransitionLayout);
}

void TransWidget::AcceptTrans()
{
    if(edited==NULL)
    {
        emit reportError(QString().fromStdString("Please, select a transition to edit, edit it and then press OK."));
        OKButton->setDisabled(true);
        sourceNameLabel->setText(QString());
        destNameLabel->setText(QString());
        return;
    }
    if(!mod->checkTransitonExists(edited))
    {
        emit reportError(QString().fromStdString("The Transition You have been editing has been deleted"));
        edited=NULL;
        OKButton->setDisabled(true);
        sourceNameLabel->setText(QString());
        destNameLabel->setText(QString());
        return;
    }
    edited->setCondition(conditionLineEdit->text());
    edited->setSubtask(stateCombo->currentText().toStdString());
    OKButton->setDisabled(false);
    sourceNameLabel->setText(QString());//TO EDIT
    destNameLabel->setText(QString());

}

void TransWidget::lengthChanged(QString newString)
{
    if(newString.size()>0)
    {
        //OKButton->setDisabled(false);
        InsertButton->setDisabled(false);
    }
    else
    {

        InsertButton->setDisabled(true);
    }
}


void TransWidget::InsertTrans()
{
    edited = NULL;
    OKButton->setDisabled(true);
    sourceNameLabel->setText(QString());
    destNameLabel->setText(QString());
    std::pair<QString, QString> thePair = std::make_pair(conditionLineEdit->text(), stateCombo->currentText());
    emit insertTransition(thePair);

}

void TransWidget::SubtaskInserted(QString newName)
{
    this->subtaskCombo->addItem(newName);
}

void TransWidget::subtaskChanged(QString name)
{
    if(subtaskCombo->currentIndex()!=-1)
    {
        stateCombo->clear();
        if(name.toStdString()!="None")
        {
            stateCombo->addItems(mod->getAllStateNames(name.toStdString()));
        }
    }
}


void TransWidget::refreshData()
{
    subtaskCombo->clear();
    subtaskCombo->addItem("None");
    subtaskCombo->addItems(mod->getTasksNameListsWithoutMain());
    subtaskChanged(subtaskCombo->currentText());
}

void TransWidget::TransSelected(Transition * trans)
{
    edited = trans;
    OKButton->setDisabled(false);
    sourceNameLabel->setText(QString());//TO EDIT
    destNameLabel->setText(QString());
    conditionLineEdit->setText(trans->getCondition());
    if(mod->getSubtaskName(QString().fromStdString(trans->getSubtask()))==std::string(""))
    {
        trans->setSubtask("");
    }
    else
    {
        subtaskCombo->setCurrentIndex(subtaskCombo->findText(QString().fromStdString(mod->getSubtaskName(QString().fromStdString(trans->getSubtask())))));
        stateCombo->setCurrentIndex(stateCombo->findText(QString().fromStdString(trans->getSubtask())));
    }
}
