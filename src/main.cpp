#include <QApplication>

#include "include/fenetrePrincipale.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    FenetrePrincipale w;
    // QQuickStyle::setStyle("Material");
    w.show();
    return a.exec();
}