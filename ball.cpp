#include "ball.h"

Ball::Ball() : QGraphicsRectItem()
{
    vx = 0, vy = 0;
    baseSpeed = BALL_BASE_SPEED;
    incrementSpeed = BALL_INCREMENT_SPEED;
    ballw = BALL_WIDTH;
    ballh = BALL_HEIGHT;
    this->setBrush(Qt::white);
    this->setRect(-ballw / 2, -ballh / 2, ballw, ballh);
}

void Ball::launch(PlayerSide side)
{
    if (side == PlayerSide::Default)
    {
        side = QRandomGenerator::global()->bounded(0, 2) ? PlayerSide::Left : PlayerSide::Right;
    }

    float randomAngle = QRandomGenerator::global()->bounded(-45, 45);
    if (side == PlayerSide::Left)
    {
        vx = -baseSpeed * qCos(qDegreesToRadians(randomAngle));
        vy = -baseSpeed * qSin(qDegreesToRadians(randomAngle));
    }
    else if (side == PlayerSide::Right)
    {
        vx = baseSpeed * qCos(qDegreesToRadians(randomAngle));
        vy = baseSpeed * qSin(qDegreesToRadians(randomAngle));
    }
}

void Ball::move()
{
    this->setPos(this->x() + vx, this->y() + vy);
}

//l'angle a régler en cas de grosse balle ><
void Ball::collision(Player* p1, Player* p2, qreal boardWidth, qreal boardHeight)
{
    qreal paddleh = p1->boundingRect().height();

    if (this->collidesWithItem(p1))
    {
        //baseSpeed = baseSpeed + baseSpeed * incrementSpeed;
        float newAngle = 45 * (p1->y() - this->y()) / (paddleh / 2);
        vx = baseSpeed * qCos(qDegreesToRadians(newAngle));
        vy = -baseSpeed * qSin(qDegreesToRadians(newAngle));
    }
    else if (this->collidesWithItem(p2))
    {
        //baseSpeed = baseSpeed + baseSpeed * incrementSpeed;
        float newAngle = 45 * (p2->y() - this->y()) / (paddleh / 2);
        vx = -baseSpeed * qCos(qDegreesToRadians(newAngle));
        vy = -baseSpeed * qSin(qDegreesToRadians(newAngle));
    }

    if (this->y() - (ballh / 2) < -boardHeight / 2)
    {
        vy = -vy;
    }
    else if (this->y() + (ballh / 2) > boardHeight / 2)
    {
        vy = -vy;
    }

    if (this->x() - (ballh / 2) < -boardWidth / 2)
    {
        emit addPoint(PlayerSide::Right);
    }
    else if (this->x() + (ballh / 2) > boardWidth / 2)
    {
        emit addPoint(PlayerSide::Left);
    }
}

void Ball::reset()
{
    this->setPos(0, 0);
}

void Ball::ballSettings(qreal ballw, qreal ballh, qreal baseSpeed, qreal incrementSpeed)
{
    this->ballw = ballw;
    this->ballh = ballh;
    this->setRect(-ballw / 2, -ballh / 2, ballw, ballh);
    this->baseSpeed = baseSpeed;
    this->incrementSpeed = incrementSpeed;
}