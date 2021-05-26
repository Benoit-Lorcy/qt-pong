#include "include/player.h"

Player::Player(PlayerSide initside, QGraphicsItem *parent)
    : QGraphicsRectItem(parent), side(initside) {
    goUp = false;
    goDown = false;

    speed = PADDLE_SPEED;
    paddlew = PADDLE_WIDTH;
    paddleh = PADDLE_HEIGHT;
    paddleDistance = PADDLE_DISTANCE;

    this->setBrush(Qt::white);
    reset(BOARD_WIDTH, BOARD_HEIGHT);
}

// Permet d'update la position des paddles à chaque tick
void Player::move(int boardWidth, int boardHeight) {
    Q_UNUSED(boardWidth);
    // qDebug() << "alert";
    if (goUp && goDown) {
        return;
    } else if (goUp && (this->y() - (paddleh / 2) > -boardHeight / 2)) {
        this->setPos(this->x(), this->y() - speed);
    } else if (goDown && (this->y() + (paddleh / 2) < boardHeight / 2)) {
        this->setPos(this->x(), this->y() + speed);
    }
}

// Permet de mettre ou remettre les paddles au milieu du terrain
void Player::reset(int boardWidth, int boardHeight) {
    Q_UNUSED(boardHeight);
    score = 0;
    if (side == PlayerSide::Left) {
        this->setRect(-(boardWidth / 2) - (paddlew / 2) + (paddleDistance),
                      -paddleh / 2, paddlew, paddleh);
    } else if (side == PlayerSide::Right) {
        this->setRect(+(boardWidth / 2) - (paddlew / 2) - (paddleDistance),
                      -paddleh / 2, paddlew, paddleh);
    }
}

// Permet d'actualiser les paddles avec les nouveau paramètres de la fenetre
// settings
void Player::paddlesSettings(qreal paddlew, qreal paddleh, qreal distance,
                             qreal vitesse) {
    this->paddlew = paddlew;
    this->paddleh = paddleh;
    this->paddleDistance = distance;
    this->speed = vitesse;
    if (side == PlayerSide::Left) {
        this->setRect(-(BOARD_WIDTH / 2) - (paddlew / 2) + (paddleDistance),
                      -paddleh / 2, paddlew, paddleh);
    } else if (side == PlayerSide::Right) {
        this->setRect(+(BOARD_WIDTH / 2) - (paddlew / 2) - (paddleDistance),
                      -paddleh / 2, paddlew, paddleh);
    }
}