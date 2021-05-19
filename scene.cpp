#include "scene.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent)
{
    p1 = new Player(PlayerSide::Left);
    p2 = new Player(PlayerSide::Right);
    score1 = new QGraphicsTextItem();
    score2 = new QGraphicsTextItem();
    ball = new Ball();
    background_image = QPixmap("chat.jpg");
    timer = new QTimer(this);
    info = new QGraphicsTextItem();
    pause = true;
    end = false;

    boardWidth = BOARD_WIDTH;
    boardHeight = BOARD_HEIGHT;
    keyPause = KEY_PAUSE;
    keyP1Up = KEY_P1_UP;
    keyP1Down = KEY_P1_DOWN;
    keyP2Up = KEY_P2_UP;
    keyP2Down = KEY_P2_DOWN;
    textSize = TEXT_SIZE;
    scoreToWin = SCORE_TO_WIN;

    setText(info, PlayerSide::Default);
    setText(score1, PlayerSide::Left);
    setText(score2, PlayerSide::Right);
    setMiddleLine();

    this->addItem(score1);
    this->addItem(score2);
    this->addItem(middleLine);
    this->addItem(p1);
    this->addItem(p2);
    this->addItem(ball);
    this->addItem(info);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(ball, SIGNAL(addPoint(PlayerSide)), this, SLOT(addPoint(PlayerSide)));

    timer->start(30);
    ball->launch();
}

void Scene::update()
{
    if (pause)
    {
        return;
    }

    ball->collision(p1, p2, boardWidth, boardHeight);
    ball->move();
    p1->move(boardWidth, boardHeight);
    p2->move(boardWidth, boardHeight);
}

void Scene::addPoint(PlayerSide side)
{
    if (side == PlayerSide::Left)
    {
        p1->setScore(p1->getScore() + 1);
        score1->setPlainText(QString::number(p1->getScore()));
        checkWin();
        ball->reset();
        ball->launch(PlayerSide::Right);
    }
    else if (side == PlayerSide::Right)
    {
        p2->setScore(p2->getScore() + 1);
        score2->setPlainText(QString::number(p2->getScore()));
        checkWin();
        ball->reset();
        ball->launch(PlayerSide::Left);
    }
}

void Scene::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    //qDebug() << event->key();

    if (key == keyPause)
    {
        if (end)
        {
            end = !end;
            reset();
            return;
        }

        pause = !pause;
        if (pause)
        {
            printInfo("Pause");
        }
        else
        {
            info->hide();
        }
    }

    if (key == keyP1Up)
    {
        p1->setUpPressed(true);
    }
    else if (key == keyP1Down)
    {
        p1->setDownPressed(true);
    }
    else if (key == keyP2Up)
    {
        p2->setUpPressed(true);
    }
    else if (key == keyP2Down)
    {
        p2->setDownPressed(true);
    }
}

void Scene::keyReleaseEvent(QKeyEvent* event)
{
    int key = event->key();
    if (key == keyP1Up)
    {
        p1->setUpPressed(false);
    }
    else if (key == keyP1Down)
    {
        p1->setDownPressed(false);
    }
    else if (key == keyP2Up)
    {
        p2->setUpPressed(false);
    }
    else if (key == keyP2Down)
    {
        p2->setDownPressed(false);
    }
}

void Scene::setText(QGraphicsTextItem* text, PlayerSide side)
{
    if (side != PlayerSide::Default)
    {
        text->setPlainText("0");
        text->setScale(textSize);
        text->setDefaultTextColor(Qt::white);
        QRectF rect = text->boundingRect();
        if (side == PlayerSide::Left)
        {
            text->setPos(textSize * (-rect.width() / 2) - (boardWidth / 4), textSize * (-rect.height() / 2) - (boardHeight / 4));
        }
        else if (side == PlayerSide::Right)
        {
            text->setPos(textSize * (-rect.width() / 2) + (boardWidth / 4), textSize * (-rect.height() / 2) - (boardHeight / 4));
        }
    }
    else
    {
        text->setDefaultTextColor(Qt::gray);
        textSize = textSize / 2;
        text->setScale(textSize);
        text->setPlainText("Press space to start !");

        QRectF rect = text->boundingRect();

        text->setPos(textSize * (-rect.width() / 2), textSize * (-rect.height() / 2));
    }
}

void Scene::setMiddleLine()
{
    QPen pen;

    pen.setStyle(Qt::DashLine);
    pen.setWidth(3);
    pen.setBrush(Qt::white);

    middleLine = new QGraphicsLineItem(3 / 2, -boardHeight / 2, 0, boardHeight / 2 - 5);
    middleLine->setPen(pen);
}

void Scene::drawBackground(QPainter* painter, const QRectF& rect)
{
    painter->setBrush((QBrush)Qt::green);
    painter->drawRect(rect);

    /*QRectF source(0.0, 0.0, background_image.width(), background_image.height());
    painter->drawPixmap(rect, background_image, source);*/
}

void Scene::checkWin()
{
    if (p1->getScore() == scoreToWin)
    {
        printInfo("Player 1 wins");
        end = true;
    }
    else if (p2->getScore() == scoreToWin)
    {
        printInfo("Player 2 wins");
        end = true;
    }
}

void Scene::printInfo(QString text)
{
    pause = true;
    info->setPlainText(text);
    QRectF rect = info->boundingRect();
    info->setPos(textSize * (-rect.width() / 2), textSize * (-rect.height() / 2));
    info->show();
}

void Scene::reset()
{
    ball->reset();
    p1->reset(boardWidth, boardHeight);
    p2->reset(boardWidth, boardHeight);
    score1->setPlainText("0");
    score2->setPlainText("0");
    printInfo("Press space to start !");
}