#ifndef VIEW_H
#define VIEW_H
#include <QtWidgets>

#include "scene.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(Scene *scene, QWidget *parent = nullptr);
    Scene *scene;
    ~View() {}

    void resizeEvent(QResizeEvent *event);
};
#endif