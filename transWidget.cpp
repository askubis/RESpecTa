#include "transWidget.h"
#include <QtGui>
#include "GraphFunctions.h"
#include "GraphFunctions.cpp"
#include "respecta.h"
#include "GlobalVariables.h"

using namespace boost;

TransWidget::TransWidget(QWidget *parent)
: QWidget(parent)
{

    //creating TRansition edit options
    TransitionLayout = new QVBoxLayout;
    transCondLabel = new QLabel(tr("Transition condition:"));
    transCondEdit = new QLineEdit;
    connect(transCondEdit, SIGNAL(textChanged(QString)), this, SLOT(lengthChanged(QString)));
    QHBoxLayout *bottomLayout = new QHBoxLayout;

//subtask combobox, subtask checkbox
//stateSource combobox, stateTarget combobox

   TransitionLayout->addWidget(transCondLabel);
   TransitionLayout->addWidget(transCondEdit);

    sourceCombo = new QComboBox(this);
    QStringList sourceItems = getStateNames(vertices(myGraph).first, vertices(myGraph).second, myGraph);
    sourceCombo->addItems(sourceItems);


   TransitionLayout->addWidget(sourceCombo);






   OKButton = new QPushButton(tr("&OK"));
   OKButton->setChecked(false);
   connect(OKButton, SIGNAL(clicked()), this, SLOT(AcceptTrans()));
   bottomLayout->addWidget(OKButton);



   InsertButton = new QPushButton(tr("&Insert"));
   InsertButton->setChecked(false);
   connect(InsertButton, SIGNAL(clicked()), this, SLOT(InsertTrans()));
   bottomLayout->addWidget(InsertButton);


   TransitionLayout->addLayout(bottomLayout);


   setLayout(TransitionLayout);
}

void TransWidget::AcceptTrans()
{
    //exit(1);
}

void TransWidget::lengthChanged(QString newString)
{

}


void TransWidget::InsertTrans()
{


}
