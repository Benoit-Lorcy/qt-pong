#ifndef CONFIG_WINDOW
#define CONFIG_WINDOW

#include <QtWidgets>

#include "include/constants.h"
class ConfigWindow : public QWidget {
    Q_OBJECT

   public:
    ConfigWindow();
    ~ConfigWindow() {}
    // QGroupBox* BuildGroupBoxControle();

   signals:
    void ballSettings(qreal ballw, qreal ballh, qreal baseSpeed,
                      qreal incrementSpeed);
    void paddlesSettings(qreal paddlew, qreal paddleh, qreal distance,
                         qreal vitesse);
    void sceneSettings(qreal textSize, qreal scoreToWin, qreal volume);
    // void ControlesSettings(qreal baseSpeed, qreal incrementSpeed, qreal
    // ballw, qreal ballh);

   private:
    QGridLayout *grid;
    QWidget *widget_principal;
    QGroupBox *createBalleGroup();
    QGroupBox *createPaddlesGroup();
    QGroupBox *createSceneGroup();

    QVector<QSlider *> sceneList;
    QVector<QSlider *> paddlesList;
    QVector<QSlider *> ballList;

    void reset();

    void submitChanges();

    void addCustomSlider(QString name, QGridLayout *grid, int current, int min,
                         int max, QVector<QSlider *> &ballGroup);
    void addCustomKeyInput(QString name, QGridLayout *grid, int current,
                           QVector<QSlider *> &list);
};

#endif