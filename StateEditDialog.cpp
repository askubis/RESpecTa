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
    items << tr("SYSTEM_INITIALIZATION") << tr("RUN_GENERATOR") << tr("EMPTY_GEN_FOR_SET") << tr("EMPTY_GEN, WAIT") <<
            tr("STOP_GEN, CUBE_STATE_INIT") << tr("INITIATE_SENSOR_READING") << tr("GET_SENSOR_READING") <<
            tr("CUBE_STATE_WRITING, CUBE_STATE_CHANGE") << tr("COMMUNICATE_WITH_SOLVER") <<
            tr("MANIPULATION_SEQ_TRANSLATION,");
    genTypeCombo = new QComboBox(this);
    genTypeCombo->addItems(items);
    genTypeCombo->setVisible(true);

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(nameLabel);
    topLeftLayout->addWidget(stateName);
    topLeftLayout->addWidget(typeAcceptedButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(topLeftLayout, 0, 0);
    mainLayout->addWidget(genTypeCombo, 1,0 );
    //mainLayout->addWidget(extension, 1, 0, 1, 2);
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
