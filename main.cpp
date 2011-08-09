#include <QtGui/QApplication>
#include "respecta.h"
#include "Model.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model * mod =new Model();
    RESpecTa* res = new RESpecTa (mod);
    res->setGeometry(100, 100, 1200, 900);
    res->show();
    mod->setView(res);
    res->CenterOn("INIT");
    return a.exec();
}

