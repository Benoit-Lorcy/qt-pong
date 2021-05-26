#include "include/scene.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    // initialistion des variables qui n'ont pas pour but d'être changées
    p1 = new Player(PlayerSide::Left);
    p2 = new Player(PlayerSide::Right);
    score1 = new QGraphicsTextItem();
    score2 = new QGraphicsTextItem();
    ball = new Ball();
    // background_image = QPixmap("chat.jpg");
    pointSound.setSource(QUrl::fromLocalFile("assets/pointScored.wav"));
    winnerSound.setSource(QUrl::fromLocalFile("assets/winner.wav"));
    timer = new QTimer(this);
    info = new QGraphicsTextItem();
    pause = true;
    end = false;

    // initialisation variables avec constants.h
    boardWidth = BOARD_WIDTH;
    boardHeight = BOARD_HEIGHT;
    keyPause = KEY_PAUSE;
    keyP1Up = KEY_P1_UP;
    keyP1Down = KEY_P1_DOWN;
    keyP2Up = KEY_P2_UP;
    keyP2Down = KEY_P2_DOWN;
    keyFullscreen = KEY_FULL_SCREEN;
    textSize = TEXT_SIZE;
    scoreToWin = SCORE_TO_WIN;

    // initialisation des textes et de la ligne centrale
    setText(info, PlayerSide::Default);
    setText(score1, PlayerSide::Left);
    setText(score2, PlayerSide::Right);
    setMiddleLine();

    // on met nos différents elements dans la scène
    this->addItem(score1);
    this->addItem(score2);
    this->addItem(middleLine);
    this->addItem(p1);
    this->addItem(p2);
    this->addItem(ball);
    this->addItem(info);

    // initialisation des connect pour l'update et l'addition des points
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(ball, SIGNAL(addPoint(PlayerSide)), this,
            SLOT(addPoint(PlayerSide)));

    // la partie commence
    timer->start(30);
    ball->launch();
}

// Permet de mettre a jour le plateau de jeux à chaque tick
void Scene::update() {
    if (pause) {
        return;
    }

    ball->collision(p1, p2, boardWidth, boardHeight);
    ball->move();
    p1->move(boardWidth, boardHeight);
    p2->move(boardWidth, boardHeight);
}

// Permet d'ajouter un point aux jouers, de relancer la balle et de vérifier si
// un joueur a gagné
void Scene::addPoint(PlayerSide side) {
    if (side == PlayerSide::Left) {
        p1->setScore(p1->getScore() + 1);
        score1->setPlainText(QString::number(p1->getScore()));
        checkWin();
        ball->reset();
        ball->launch(PlayerSide::Right);
    } else if (side == PlayerSide::Right) {
        p2->setScore(p2->getScore() + 1);
        score2->setPlainText(QString::number(p2->getScore()));
        checkWin();
        ball->reset();
        ball->launch(PlayerSide::Left);
    }
}

// Permet de savoir si une touche est préssée
void Scene::keyPressEvent(QKeyEvent* event) {
    int key = event->key();

    // permet de mettre le jeux en pause ou d'arrêter l'état de fin du jeu
    if (key == keyPause) {
        if (end) {
            end = !end;
            reset();
            return;
        }

        pause = !pause;
        if (pause) {
            printInfo("Pause");
        } else {
            info->hide();
        }
    }

    // combinée a la méthode suivante, permet d'avoir des paddles fluides
    if (key == keyP1Up) {
        p1->setUpPressed(true);
    } else if (key == keyP1Down) {
        p1->setDownPressed(true);
    } else if (key == keyP2Up) {
        p2->setUpPressed(true);
    } else if (key == keyP2Down) {
        p2->setDownPressed(true);
    }

    if (key == keyFullscreen) {
        emit FullScreenUpdate();
    }
}

// Permet de savoir si une touche est relachée
void Scene::keyReleaseEvent(QKeyEvent* event) {
    int key = event->key();

    // combinée a la méthode si dessus, permet d'avoir des paddles fluides
    if (key == keyP1Up) {
        p1->setUpPressed(false);
    } else if (key == keyP1Down) {
        p1->setDownPressed(false);
    } else if (key == keyP2Up) {
        p2->setUpPressed(false);
    } else if (key == keyP2Down) {
        p2->setDownPressed(false);
    }
}

// permet d'initiliser un texte et de la placer sur le plateau
void Scene::setText(QGraphicsTextItem* text, PlayerSide side) {
    if (side != PlayerSide::Default) {
        if (text->toPlainText() == "") {
            text->setPlainText("0");
        }
        text->setScale(textSize);
        text->setDefaultTextColor(Qt::white);
        QRectF rect = text->boundingRect();
        if (side == PlayerSide::Left) {
            text->setPos(textSize * (-rect.width() / 2) - (boardWidth / 4),
                         textSize * (-rect.height() / 2) - (boardHeight / 4));
        } else if (side == PlayerSide::Right) {
            text->setPos(textSize * (-rect.width() / 2) + (boardWidth / 4),
                         textSize * (-rect.height() / 2) - (boardHeight / 4));
        }
    } else {
        text->setDefaultTextColor(Qt::gray);
        textSize = textSize / 2;
        text->setScale(textSize);
        text->setPlainText("Press space to start !");  // Press space to start !

        QRectF rect = text->boundingRect();

        text->setPos(textSize * (-rect.width() / 2),
                     textSize * (-rect.height() / 2));
    }
}

// On met en place la ligne du milieu
void Scene::setMiddleLine() {
    QPen pen;

    pen.setStyle(Qt::DashLine);
    pen.setWidth(3);
    pen.setBrush(Qt::white);

    middleLine =
        new QGraphicsLineItem(3 / 2, -boardHeight / 2, 0, boardHeight / 2 - 5);
    middleLine->setPen(pen);
}

// Permet de changer le fond, néamoins cette methode de fonctionne pas
// correctement Si le code est décomenté des lignes noires sont formés sur
// l'image après le passage de la balle
void Scene::drawBackground(QPainter* painter, const QRectF& rect) {
    painter->setBrush((QBrush)Qt::black);
    painter->drawRect(rect);

    /*QRectF source(0.0, 0.0, background_image.width(),
    background_image.height()); painter->drawPixmap(rect, background_image,
    source);*/
}

// On regarde si un joueur a ganger, si qqn a gagner, c'est la fin de la partie
void Scene::checkWin() {
    if (p1->getScore() >= scoreToWin) {
        winnerSound.play();
        printInfo("Player 1 wins");  // Player 1 wins
        end = true;
    } else if (p2->getScore() >= scoreToWin) {
        winnerSound.play();
        printInfo("Player 2 wins");  // Player 2 wins
        end = true;
    } else {
        pointSound.play();
    }
}

// Permet d'afficher le texte central centré selon la longueur du texte
void Scene::printInfo(QString text) {
    pause = true;
    info->setPlainText(text);
    QRectF rect = info->boundingRect();
    info->setPos(textSize * (-rect.width() / 2),
                 textSize * (-rect.height() / 2));
    info->show();
}

// Permet de remettre à 0 les attribus de classes pour remettre a 0 la partie
void Scene::reset() {
    p1->reset(boardWidth, boardHeight);
    p2->reset(boardWidth, boardHeight);
    score1->setPlainText("0");
    score2->setPlainText("0");
    printInfo("Press space to start !");
}

// Permet d'actualiser la scene avec les nouveau paramètres de la fenetre
// settings
void Scene::sceneSettings(qreal textSize, qreal scoreToWin, qreal volume) {
    this->textSize = textSize;
    this->scoreToWin = scoreToWin;

    setText(score1, PlayerSide::Left);
    setText(score2, PlayerSide::Right);
    setText(info);

    ball->getSound().setVolume(volume * 0.01);
    winnerSound.setVolume(volume * 0.01);
    pointSound.setVolume(volume * 0.01);
}