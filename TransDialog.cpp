#include "TransDialog.h"

TransDialog::TransDialog(QWidget * parent, Model * newmod):QDialog(parent)
{
    mod = newmod;
    setWindowTitle(tr("Pose"));
    QGridLayout * mainLayout = new QGridLayout;
    QLabel * label1 = new QLabel("Condition:");
    QLabel * label2 = new QLabel("Target:");
    QLabel * label3 = new QLabel("Subtask:");
    mainLayout->addWidget(label1, 0,0);
    mainLayout->addWidget(label2, 0,1);
    mainLayout->addWidget(label3, 0,2);

    transCondList = new QListWidget();
    mainLayout->addWidget(transCondList, 1,0,7,1);
    connect(transCondList, SIGNAL(currentRowChanged(int)), this, SLOT(RowChanged(int)));
    transTargList = new QListWidget();
    mainLayout->addWidget(transTargList, 1,1,7,1);
    connect(transTargList, SIGNAL(currentRowChanged(int)), this, SLOT(RowChanged(int)));
    transSubList = new QListWidget();
    mainLayout->addWidget(transSubList, 1,2,7,1);
    connect(transSubList, SIGNAL(currentRowChanged(int)), this, SLOT(RowChanged(int)));



    QPushButton * UpButton = new QPushButton("Up");
    connect(UpButton, SIGNAL(clicked()), this, SLOT(UpPressed()));
    QPushButton * DownButton = new QPushButton("Down");
    connect(DownButton, SIGNAL(clicked()), this, SLOT(DownPressed()));
    QPushButton * OKButton = new QPushButton("OK");
    connect(OKButton, SIGNAL(clicked()), this, SLOT(OKPressed()));
    mainLayout->addWidget(UpButton,0,4);
    mainLayout->addWidget(DownButton,1,4);
    mainLayout->addWidget(OKButton,2,4);




    this->setGeometry(0,0,500,400);
    this->setLayout(mainLayout);
}

void TransDialog::openForAState(BaseState * tmp)
{
    state = tmp;
    setWindowTitle(tr(("Editing transitions for state "+tmp->getName().toStdString()).c_str()));
    transCondList->clear();
    transTargList->clear();
    transSubList->clear();
    std::vector<Transition *> tranList=mod->getTransitions(tmp);
    foreach(Transition * tr, tranList)
    {
        transCondList->addItem(tr->getCondition());
        transTargList->addItem(tr->endItem()->getName());
        transSubList->addItem(QString().fromStdString(tr->getSubtask()));
    }
    RowChanged(0);

}

void TransDialog::RowChanged(int index)
{
    transCondList->setCurrentRow(index);
    transTargList->setCurrentRow(index);
    transSubList->setCurrentRow(index);
}

void TransDialog::OKPressed()
{
    this->setVisible(false);
}

void TransDialog::DownPressed()
{
    int index = transCondList->currentIndex().row();
    if(index==state->getTransitions().size()-1)
    {
        emit reportError(QString().fromStdString("Cannot move the last transition down"));
        return;
    }
    mod->MoveTransitionDown(state,index);
    openForAState(state);

    RowChanged(index+1);
}

void TransDialog::UpPressed()
{
    int index = transCondList->currentIndex().row();
    if(index<0)
    {
        emit reportError(QString().fromStdString("A transition has to be selected"));
    }
    if(index==0)
    {
        emit reportError(QString().fromStdString("Cannot move the first transition up"));
        return;
    }
    mod->MoveTransitionUp(state,index);
    openForAState(state);
    RowChanged(index-1);
}
