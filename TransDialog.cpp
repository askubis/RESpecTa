#include "TransDialog.h"

TransDialog::TransDialog(QWidget * parent, Model * newmod):QDialog(parent)
{
    mod = mod;
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
    transTargList = new QListWidget();
    mainLayout->addWidget(transTargList, 1,1,7,1);
    transSubList = new QListWidget();
    mainLayout->addWidget(transSubList, 1,2,7,1);

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
    transCondList->clear();
    transTargList->clear();
    transSubList->clear();
    QList<Transition *> tranList = tmp->getTransitions();
    foreach(Transition * tr, tranList)
    {
        transCondList->addItem(tr->getCondition());
        transTargList->addItem(tr->endItem()->getName());
        transSubList->addItem(QString().fromStdString(tr->getSubtask()));
    }
}

void TransDialog::OKPressed()
{
    this->setVisible(false);
}

void TransDialog::DownPressed()
{

}

void TransDialog::UpPressed()
{

}
