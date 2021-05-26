#ifndef BALL_H
#define BALL_H

#include <QSoundEffect>
#include <QtWidgets>

#include "include/constants.h"
#include "include/player.h"

class Ball : public QObject, public QGraphicsRectItem {
    Q_OBJECT
   public:
    Ball();
    ~Ball() {}
    void launch(PlayerSide side = PlayerSide::Default);
    void collision(Player* p1, Player* p2, qreal boardWidth, qreal boardHeight);
    void reset();
    void move();
    QSoundEffect& getSound() { return bounceSound; }

   signals:
    void addPoint(PlayerSide side);

   public slots:
    void ballSettings(qreal ballw, qreal ballh, qreal baseSpeed,
                      qreal incrementSpeed);

   private:
    qreal vx, vy;
    qreal baseSpeed;
    qreal incrementSpeed;
    qreal currentSpeed;
    qreal ballw;
    qreal ballh;
    QSoundEffect bounceSound;
};

#endif