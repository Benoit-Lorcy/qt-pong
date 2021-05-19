#include "view.h"

View::View(Scene* s, QWidget* parent) : QGraphicsView(s, parent), scene(s)
{
    // this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    float ratio = (float)this->width() / this->height();
    int w = BOARD_HEIGHT * ratio;
    int h = BOARD_HEIGHT;

    qDebug() << this->width() << this->height() << ratio << w << h;

    this->setSceneRect(-w / 2, -h / 2, w, h);
    this->fitInView(sceneRect());
}