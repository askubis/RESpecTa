#include "StateEditDialog.h"

#include <QtGui>

StateEditDialog::StateEditDialog(QWidget *parent)
    : QDialog(parent)
{
    nameLabel = new QLabel(tr("State Name:"));
    stateName = new QLineEdit;
    nameLabel->setBuddy(stateName);

    typeAcceptedButton = new QPushButton(tr("&Continue"));
    typeAcceptedButton->setDefault(true);
    connect(typeAcceptedButton, SIGNAL(clicked()), this, SLOT(typeAccepted()));

    QStringList items;
    items << tr("SYSTEM_INITIALIZATION") << tr("RUN_GENERATOR") << tr("EMPTY_GEN_FOR_SET") << tr("EMPTY_GEN") << tr("WAIT") <<
            tr("STOP_GEN") << tr("CUBE_STATE_INIT") << tr("INITIATE_SENSOR_READING") << tr("GET_SENSOR_READING") <<
            tr("CUBE_STATE_WRITING") << tr("CUBE_STATE_CHANGE") << tr("COMMUNICATE_WITH_SOLVER") <<
            tr("MANIPULATION_SEQ_TRANSLATION,");
    genTypeCombo = new QComboBox(this);
    genTypeCombo->addItems(items);
    genTypeCombo->setVisible(true);
    setStateSubclass(genTypeCombo->currentIndex());

    connect(genTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setStateSubclass(int)));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(nameLabel);
    topLeftLayout->addWidget(stateName);
    topLeftLayout->addWidget(typeAcceptedButton);

    mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(topLeftLayout, 0, 0);
    mainLayout->addWidget(genTypeCombo, 1,0 );
    mainLayout->addWidget(extension, 2,0);
    setLayout(mainLayout);

    setWindowTitle(tr("Stan"));




}
void StateEditDialog::typeAccepted()
{
    if (stateName->text().size()!=0)
    {
        this->close();
    }

}


void StateEditDialog::setStateSubclass(int chosen)
{
    QWidget *tmp = new QWidget;
    QVBoxLayout *tmpLayout = new QVBoxLayout;
    tmpLayout->setMargin(0);
    tmp->setLayout(tmpLayout);
    switch(chosen)
    {
    case SYSTEM_INITIALIZATION:

        extension=tmp;
        extension->setVisible(true);
        break;
    default:

        break;
    }

}
