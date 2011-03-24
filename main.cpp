#include <QtGui/QApplication>
#include "respecta.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RESpecTa w;
    w.setGeometry(100, 100, 1200, 800);
    w.show();

    return a.exec();
}
