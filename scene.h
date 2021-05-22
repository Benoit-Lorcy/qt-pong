#ifndef SCENE_H
#define SCENE_H
#include <QtWidgets>

#include "ball.h"
#include "constants.h"
#include "player.h"

class Scene : public QGraphicsScene {
    Q_OBJECT
   public:
    Scene(QObject* parents = 0);
    ~Scene() {}
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void setMiddleLine();
    void setText(QGraphicsTextItem* text,
                 PlayerSide side = PlayerSide::Default);
    void checkWin();
    void printInfo(QString text);
    void reset();

    Ball* getBall() { return this->ball; }
    Player* getP1() { return this->p1; }
    Player* getP2() { return this->p2; }

   public slots:
    void update();
    void addPoint(PlayerSide side);
    void sceneSettings(qreal textSize, qreal scoreToWin);

   private:
    bool pause, end;
    QGraphicsTextItem *score1, *score2;
    QGraphicsTextItem* info;
    QGraphicsLineItem* middleLine;
    Player *p1, *p2;
    Ball* ball;
    QPixmap background_image;
    QTimer* timer;
    int boardWidth, boardHeight;
    int keyPause, keyP1Up, keyP1Down, keyP2Up, keyP2Down;
    int scoreToWin;
    qreal textSize;
};

#endif