#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <vector>

#include "fenetrePrincipale.h"

int main(int argc, char *argv[]) {
    // au secour
    QApplication a(argc, argv);
    FenetrePrincipale w;
    QQuickStyle::setStyle("Material");
    w.show();
    return a.exec();
}