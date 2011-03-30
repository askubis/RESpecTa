/********************************************************************************
** Form generated from reading UI file 'respecta.ui'
**
** Created: Wed Mar 30 16:52:08 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESPECTA_H
#define UI_RESPECTA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RESpecTa
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RESpecTa)
    {
        if (RESpecTa->objectName().isEmpty())
            RESpecTa->setObjectName(QString::fromUtf8("RESpecTa"));
        RESpecTa->resize(800, 600);
        centralWidget = new QWidget(RESpecTa);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        RESpecTa->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RESpecTa);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 25));
        RESpecTa->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RESpecTa);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        RESpecTa->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RESpecTa);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        RESpecTa->setStatusBar(statusBar);

        retranslateUi(RESpecTa);

        QMetaObject::connectSlotsByName(RESpecTa);
    } // setupUi

    void retranslateUi(QMainWindow *RESpecTa)
    {
        RESpecTa->setWindowTitle(QApplication::translate("RESpecTa", "RESpecTa", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RESpecTa: public Ui_RESpecTa {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESPECTA_H
