#ifndef BALL_H
#define BALL_H

#include <QtWidgets>

#include "constants.h"
#include "player.h"

class Ball : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Ball();
    ~Ball() {}
    void launch(PlayerSide side = PlayerSide::Default);
    void collision(Player* p1, Player* p2, qreal boardWidth, qreal boardHeight);
    void reset();
    void move();

signals:
    void addPoint(PlayerSide side);

public slots:
    void ballSettings(qreal ballw, qreal ballh, qreal baseSpeed, qreal incrementSpeed);

private:
    qreal vx, vy;
    qreal baseSpeed;
    qreal incrementSpeed;
    qreal ballw;
    qreal ballh;
};

#endif