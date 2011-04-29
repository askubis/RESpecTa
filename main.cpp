#include <QtGui/QApplication>
#include "respecta.h"
#include "Controller.h"
#include "Model.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model * mod =new Model();
    Controller * cont =new Controller(mod);
    RESpecTa* res = new RESpecTa (mod, cont);
    res->setGeometry(100, 100, 1200, 800);
    res->show();
    cont->setView(res);

    return a.exec();
}

