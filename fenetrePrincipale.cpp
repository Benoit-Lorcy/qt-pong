#include "fenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale() : QMainWindow() {
    // le widget dans lequel tout s'affiche
    this->setWindowTitle("Mafenetregraphique");
    this->setMinimumWidth(BOARD_WIDTH);
    this->setMinimumHeight(BOARD_HEIGHT /*+ 30*/);

    conf = new ConfigWindow();
    conf->show();

    mainScene = new Scene(this);
    mainView = new View(mainScene, this);

    // menuConfig = menuBar()->addMenu(tr("&Config"));
    // menuConfig->addAction(show_config_window);
    // this->setAttribute(Qt::WA_DeleteOnClose);

    connect(conf, SIGNAL(ballSettings(qreal, qreal, qreal, qreal)),
            mainScene->getBall(),
            SLOT(ballSettings(qreal, qreal, qreal, qreal)));

    connect(conf, SIGNAL(paddlesSettings(qreal, qreal, qreal, qreal)),
            mainScene->getP1(),
            SLOT(paddlesSettings(qreal, qreal, qreal, qreal)));

    connect(conf, SIGNAL(paddlesSettings(qreal, qreal, qreal, qreal)),
            mainScene->getP2(),
            SLOT(paddlesSettings(qreal, qreal, qreal, qreal)));

    connect(conf, SIGNAL(sceneSettings(qreal, qreal)), mainScene,
            SLOT(sceneSettings(qreal, qreal)));
    this->setCentralWidget(mainView);
}

FenetrePrincipale::~FenetrePrincipale() {}
