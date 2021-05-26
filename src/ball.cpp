#include "include/ball.h"

Ball::Ball() : QGraphicsRectItem() {
    // Initialisation des variables de la balle
    vx = 0, vy = 0;
    baseSpeed = BALL_BASE_SPEED;
    currentSpeed = BALL_BASE_SPEED;
    incrementSpeed = BALL_INCREMENT_SPEED;
    ballw = BALL_WIDTH;
    ballh = BALL_HEIGHT;
    this->setBrush(Qt::white);
    this->setRect(-ballw / 2, -ballh / 2, ballw, ballh);
    bounceSound.setSource(QUrl::fromLocalFile("assets/bounce.wav"));
}

// Permet de lancer la balle vers un joueurs
// Si aucun joueur n'est précisier, elle lancera la balle est un joueur
// aléatoire
void Ball::launch(PlayerSide side) {
    if (side == PlayerSide::Default) {
        side = QRandomGenerator::global()->bounded(0, 2) ? PlayerSide::Left
                                                         : PlayerSide::Right;
    }

    float randomAngle = QRandomGenerator::global()->bounded(-45, 45);
    if (side == PlayerSide::Left) {
        vx = -baseSpeed * qCos(qDegreesToRadians(randomAngle));
        vy = -baseSpeed * qSin(qDegreesToRadians(randomAngle));
    } else if (side == PlayerSide::Right) {
        vx = baseSpeed * qCos(qDegreesToRadians(randomAngle));
        vy = baseSpeed * qSin(qDegreesToRadians(randomAngle));
    }
}

// Permet d'update la position de la balle chaque tick
void Ball::move() { this->setPos(this->x() + vx, this->y() + vy); }

// Collision avec une raquette ou les murs du "plateau" de jeu
// Si la balle touche un player, elle va être renvoyée avec un nouvel angle
// Si balle n'est pas renvoyée, un signal va être envoyé a la scène
void Ball::collision(Player* p1, Player* p2, qreal boardWidth,
                     qreal boardHeight) {
    qreal paddleh = p1->boundingRect().height();

    if (this->collidesWithItem(p1)) {
        bounceSound.play();
        currentSpeed = currentSpeed + baseSpeed * incrementSpeed * 0.01;
        float newAngle = 45 * (p1->y() - this->y()) / (paddleh / 2);
        if (newAngle >= 45) {
            newAngle = 45;
        } else if (newAngle <= -45) {
            newAngle = -45;
        }
        vx = currentSpeed * qCos(qDegreesToRadians(newAngle));
        vy = -currentSpeed * qSin(qDegreesToRadians(newAngle));
    } else if (this->collidesWithItem(p2)) {
        bounceSound.play();
        currentSpeed = currentSpeed + baseSpeed * incrementSpeed * 0.01;
        float newAngle = 45 * (p2->y() - this->y()) / (paddleh / 2);
        if (newAngle >= 45) {
            newAngle = 45;
        } else if (newAngle <= -45) {
            newAngle = -45;
        }
        vx = -currentSpeed * qCos(qDegreesToRadians(newAngle));
        vy = -currentSpeed * qSin(qDegreesToRadians(newAngle));
    }

    if (this->y() - (ballh / 2) < -boardHeight / 2) {
        vy = -vy;
    } else if (this->y() + (ballh / 2) > boardHeight / 2) {
        vy = -vy;
    }

    if (this->x() - (ballw / 2) < -boardWidth / 2) {
        emit addPoint(PlayerSide::Right);
    } else if (this->x() + (ballw / 2) > boardWidth / 2) {
        emit addPoint(PlayerSide::Left);
    }
}

// Permet de remettre la balle au milieu du plateau
void Ball::reset() {
    currentSpeed = baseSpeed;
    QRectF rect = this->boundingRect();
    qDebug() << rect;
    this->setPos(-2.5, -2.5);
    qDebug() << rect;
    // this->setRect(-ballw / 2, -ballh / 2, ballw, ballh);
}

// Permet d'actualiser la balle avec les nouveau paramètres de la fenetre
// settings
void Ball::ballSettings(qreal ballw, qreal ballh, qreal baseSpeed,
                        qreal incrementSpeed) {
    this->ballw = ballw;
    this->ballh = ballh;
    this->setRect(-ballw / 2, -ballh / 2, ballw, ballh);
    this->currentSpeed = baseSpeed;
    this->baseSpeed = baseSpeed;
    this->incrementSpeed = incrementSpeed;
}