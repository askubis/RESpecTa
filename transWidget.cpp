#include "transWidget.h"
#include <QtGui>

using namespace boost;

TransWidget::TransWidget(QWidget *parent,Model * newmod )
: QWidget(parent)
{
    mod = newmod;
   QVBoxLayout *TransitionLayout = new QVBoxLayout;

   QLabel *transCondLabel = new QLabel(tr("Transition condition:"));
   condTypeCombo = new QComboBox();
   condTypeCombo->addItems(getCondTypeTable());
   connect(condTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));

   conditionLineEdit = new QLineEdit;
   //conditionLineEdit->setValidator(new QRegExpValidator(QRegExp("^(stateOperationResult|true|TRUE|iniFile\\.\\w*)$"), conditionLineEdit));
   connect(conditionLineEdit, SIGNAL(textChanged(QString)), this, SLOT(lengthChanged(QString)));
   QHBoxLayout *bottomLayout = new QHBoxLayout;
   TransitionLayout->addWidget(transCondLabel);
   TransitionLayout->addWidget(condTypeCombo);
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

   OKButton = new QPushButton(tr("&Apply"));
   OKButton->setChecked(false);
   connect(OKButton, SIGNAL(clicked()), this, SLOT(AcceptTrans()));
   OKButton->setDisabled(true);
   bottomLayout->addWidget(OKButton);

   /*InsertButton = new QPushButton(tr("&Insert"));
   InsertButton->setChecked(false);
   connect(InsertButton, SIGNAL(clicked()), this, SLOT(InsertTrans()));
   InsertButton->setDisabled(true);
   bottomLayout->addWidget(InsertButton);*/

   QLabel * sourceLabel =new QLabel(tr("Source state:"));
   sourceNameCombo = new QComboBox();

   QLabel * destLabel =new QLabel(tr("Destination state:"));
   destNameCombo = new QComboBox();

   TransitionLayout->addWidget(sourceLabel);
   TransitionLayout->addWidget(sourceNameCombo);
   TransitionLayout->addWidget(destLabel);
   TransitionLayout->addWidget(destNameCombo);

   TransitionLayout->addStretch();
   TransitionLayout->addLayout(bottomLayout);
   edited = NULL;
   OKButton->setDisabled(true);
   setLayout(TransitionLayout);
}

void TransWidget::AcceptTrans()
{

    QString src = sourceNameCombo->currentText();
    QString dst = destNameCombo->currentText();
    if(edited==NULL)
    {
        emit reportError(QString("Please, select a transition to edit, edit it and then press OK."));
        OKButton->setDisabled(true);
        sourceNameCombo->clear();
        destNameCombo->clear();
        return;
    }
    if(!mod->checkTransitonExists(edited))
    {
        emit reportError(QString("The Transition You have been editing has been deleted"));
        edited=NULL;
        OKButton->setDisabled(true);
        sourceNameCombo->clear();
        destNameCombo->clear();
        return;
    }
    if (edited->startItem()->getName()==sourceNameCombo->currentText() && edited->endItem()->getName()==destNameCombo->currentText())
    {
        if(mod->checkTransCondAvailabe(edited, (ConditionType)condTypeCombo->currentIndex(), conditionLineEdit->text()))
        {
            edited->setCondition(conditionLineEdit->text());
            edited->setCondType((ConditionType)condTypeCombo->currentIndex());
            edited->setSubtask(mod->getState(stateCombo->currentText()));
            OKButton->setDisabled(false);
            edited->setToolTip(QString().fromStdString(edited->Print()));
        }
        else //that condition is already used for the source state
        {
            emit reportError(QString("The condition you specified is already in use for the source state."));
        }
    }
    else if( ( edited->startItem()->getName() == sourceNameCombo->currentText() && mod->checkTransCondAvailabe(edited,(ConditionType)condTypeCombo->currentIndex(), conditionLineEdit->text()) )
            ||mod->checkTransCondAvailabe(mod->getState(sourceNameCombo->currentText()),(ConditionType) condTypeCombo->currentIndex(), conditionLineEdit->text()))
    {
        QString subtaskName = mod->getSubNameOfTrans(edited);
        QGraphicsScene * scene = edited->getScene();
        /*if(edited->startItem()->getName()!=sourceNameCombo->currentText())
        {
            mod->changeSourceStateofTrans(edited, sourceNameCombo->currentText());
        }else{}
        if(edited->endItem()->getName()!=destNameCombo->currentText())
        {
            mod->changeDestStateofTrans(edited, destNameCombo->currentText());
        }else{}
        edited->setCondition(conditionLineEdit->text());
        edited->setSubtask(mod->getState(stateCombo->currentText()));
        OKButton->setDisabled(false);
        edited->setToolTip(QString().fromStdString(edited->Print()));*/
Transition * todelete = edited;
        mod->deleteTransition(edited);
        scene->removeItem(todelete);
        delete todelete;//?

        Transition * tr = new Transition(mod->getState(src, subtaskName), mod->getState(dst, subtaskName));
        tr->setScene(scene);
        tr->setCondType((ConditionType)condTypeCombo->currentIndex());
        tr->setCondition(conditionLineEdit->text());
        tr->setSubtask(mod->getState(stateCombo->currentText()));
        tr->startItem()->addTransition(tr);
        if(tr->startItem()!=tr->endItem())tr->endItem()->addTransition(tr);
        tr->setZValue(-1000.0);
        tr->updatePosition();

        tr->setToolTip(QString().fromStdString(tr->Print()));
        scene->addItem(tr);
        bool test = mod->tryInsertTransition(tr);

        edited=NULL;
        this->TransSelected(tr);
    }
    else
    {
        emit reportError(QString("The condition you specified is already in use for the source state."));
    }
}

void TransWidget::lengthChanged(QString newString)
{
    if(newString.size()>0)
    {
        //InsertButton->setDisabled(false);
    }
    else
    {
        //InsertButton->setDisabled(true);
    }
}

/*void TransWidget::InsertTrans()
{
    edited = NULL;
    OKButton->setDisabled(true);
    //sourceNameLabel->setText(QString());
    //destNameLabel->setText(QString());
    std::pair<QString, QString> thePair = std::make_pair(conditionLineEdit->text(), stateCombo->currentText());
    emit insertTransition(thePair);
}*/

void TransWidget::subtaskChanged(QString name)
{
    if(subtaskCombo->currentIndex()!=-1)
    {
        stateCombo->clear();
        if(name.toStdString()!="None")
        {
            stateCombo->addItems(mod->getAllStartStateNames(name));
        }
    }
}

void TransWidget::refreshData()
{
    if(edited)
    {
        if(edited->startItem()->getName()!=this->sourceNameCombo->currentText() ||
                edited->endItem()->getName()!=this->destNameCombo->currentText() ||
                edited->getCondition()!=this->conditionLineEdit->text() ||
                condTypeCombo->currentIndex()!=edited->getCondType())
        {
            AcceptTrans();
            return;
        }

        if(edited->getSubtask())
        {
            if (edited->getSubtask()->getName()!=this->stateCombo->currentText())
            {
                AcceptTrans();
                return;
            }
        }
        else
        {
            if(this->subtaskCombo->currentText()!="None")
            {
                AcceptTrans();
                return;
            }
        }
    }
edited=0;
    subtaskCombo->clear();
    subtaskCombo->addItem("None");
    subtaskCombo->addItems(mod->getTasksNameListsWithoutMain());
    subtaskChanged(subtaskCombo->currentText());
    sourceNameCombo->clear();
    destNameCombo->clear();
}

void TransWidget::TransSelected(Transition * trans)
{
    if(edited)
    {
        if(edited->startItem()->getName()!=this->sourceNameCombo->currentText() ||
                edited->endItem()->getName()!=this->destNameCombo->currentText() ||
                edited->getCondition()!=this->conditionLineEdit->text() ||
                condTypeCombo->currentIndex()!=edited->getCondType())
            AcceptTrans();
        if(edited->getSubtask())
        {
            if (edited->getSubtask()->getName()!=this->stateCombo->currentText())
                AcceptTrans();
        }
        else
        {
            if(this->subtaskCombo->currentText()!="None")
                AcceptTrans();
        }
    }
    edited = trans;
    OKButton->setDisabled(false);


    QString subtaskName=mod->getSubtaskName(trans->startItem());
    QStringList startList = mod->getAllStartStateNames(subtaskName);
    sourceNameCombo->clear();
    sourceNameCombo->addItems(startList);
    sourceNameCombo->setCurrentIndex(sourceNameCombo->findText(trans->startItem()->getName()));

    QStringList endList = mod->getAllEndStateNames(subtaskName);
    destNameCombo->clear();
    destNameCombo->addItems(endList);
    destNameCombo->setCurrentIndex(destNameCombo->findText(trans->endItem()->getName()));
    //sourceNameLabel->setText(trans->startItem()->getName());
    //destNameLabel->setText(trans->endItem()->getName());
    condTypeCombo->setCurrentIndex(trans->getCondType());
    conditionLineEdit->setText(trans->getCondition());
    if(trans->getSubtask())
    {
        if(mod->getSubtaskName(trans->getSubtask())==QString(""))
        {
            trans->setSubtask(NULL);
        }
        else
        {
            subtaskCombo->setCurrentIndex(subtaskCombo->findText(mod->getSubtaskName(trans->getSubtask())));
            stateCombo->setCurrentIndex(stateCombo->findText(trans->getSubtask()->getName()));
        }
    }
    else
    {
        stateCombo->clear();
        subtaskCombo->setCurrentIndex(0);
    }
}

void TransWidget::indexChanged(int index)
{
    if(index==INIFILE)
    {
        conditionLineEdit->setEnabled(true);
    }
    else
    {
        conditionLineEdit->setDisabled(true);
        conditionLineEdit->setText("");
    }

}
