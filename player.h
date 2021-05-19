#ifndef PLAYER_H
#define PLAYER_H

#include <QtWidgets>

#include "constants.h"

enum class PlayerSide
{
    Left = 0,
    Right = 1,
    Default = 2
};

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player(PlayerSide side, QGraphicsItem *parent = nullptr);
    ~Player() {}
    void move(int boardWidth, int boardHeight);
    void setUpPressed(bool pressed) { goUp = pressed; }
    void setDownPressed(bool pressed) { goDown = pressed; }
    int getScore() { return this->score; }
    void setScore(int newScore) { score = newScore; }
    void reset(int boardWidth, int boardHeight);

public slots:
    void paddlesSettings(qreal paddlew, qreal paddleh, qreal distance, qreal vitesse);

private:
    bool goUp, goDown;
    int score;
    int speed;
    int paddlew, paddleh;
    int paddleDistance;
    PlayerSide side;
};

#endif