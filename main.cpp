#include <QApplication>
#include <vector>

#include "fenetrePrincipale.h"

int main(int argc, char *argv[])
{
    // au secour
    QApplication a(argc, argv);
    FenetrePrincipale w;
    w.show();
    return a.exec();
}