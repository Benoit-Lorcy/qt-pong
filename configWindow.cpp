#include "configWindow.h"

ConfigWindow::ConfigWindow() : QWidget() {
    // le widget dans lequel tout s'affiche
    this->setMinimumWidth(100);
    this->setMinimumHeight(750);

    // Grid owo
    // QWidget *widget_principal = new QWidget;
    grid = new QGridLayout();
    grid->addWidget(createBalleGroup(), 0, 0);
    grid->addWidget(createPaddlesGroup(), 1, 0);
    grid->addWidget(createSceneGroup(), 2, 0);
    grid->addWidget(createControlesGroup(), 3, 0);

    // connect(ball, SIGNAL(addPoint(PlayerSide)), this,
    // SLOT(addPoint(PlayerSide))); connect(ball, SIGNAL(addPoint(PlayerSide)),
    // this, SLOT(addPoint(PlayerSide)));

    // resize(480, 320);
    // widget_principal->setLayout(grid);

    // widget_principal->setWindowTitle(tr("Group Boxes"));
    this->setLayout(grid);
}

QGroupBox *ConfigWindow::createBalleGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Balle"));
    QGridLayout *grid = new QGridLayout;

    addCustomSlider("Largeur", grid, BALL_WIDTH, 10, 400, ballList);
    addCustomSlider("Hauteur", grid, BALL_HEIGHT, 10, 400, ballList);
    addCustomSlider("Vitesse", grid, BALL_BASE_SPEED, 5, 30, ballList);
    addCustomSlider("Acceleration", grid, BALL_INCREMENT_SPEED, 0.01, 1,
                    ballList);
    groupBox->setLayout(grid);

    return groupBox;
}

QGroupBox *ConfigWindow::createPaddlesGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Paddle"));
    QGridLayout *grid = new QGridLayout;

    addCustomSlider("Largeur", grid, PADDLE_WIDTH, 1, 100, paddlesList);
    addCustomSlider("Hauteur", grid, PADDLE_HEIGHT, 1, 500, paddlesList);
    addCustomSlider("Distance", grid, PADDLE_DISTANCE, 1, 100, paddlesList);
    addCustomSlider("Vitesse", grid, PADDLE_SPEED, 1, 50, paddlesList);
    groupBox->setLayout(grid);

    return groupBox;
}

QGroupBox *ConfigWindow::createSceneGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Scene"));
    QGridLayout *grid = new QGridLayout;

    addCustomSlider("Taille texte", grid, TEXT_SIZE, 1, 16, sceneList);
    addCustomSlider("Score gagner", grid, SCORE_TO_WIN, 1, 20, sceneList);
    groupBox->setLayout(grid);

    return groupBox;
}

QGroupBox *ConfigWindow::createControlesGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Controles"));

    return groupBox;
}

void ConfigWindow::submitChanges() {
    emit ballSettings(ballList[0]->value(), ballList[1]->value(),
                      ballList[2]->value(), ballList[3]->value());
    emit paddlesSettings(paddlesList[0]->value(), paddlesList[1]->value(),
                         paddlesList[2]->value(), paddlesList[3]->value());
    emit sceneSettings(sceneList[0]->value(), sceneList[1]->value());
    // emit SceneSettings();
}

void ConfigWindow::addCustomSlider(QString name, QGridLayout *grid, int current,
                                   int min, int max, QVector<QSlider *> &list) {
    QSlider *slider = new QSlider(Qt::Horizontal);
    QLineEdit *input = new QLineEdit();
    QLabel *sliderLabel = new QLabel(name);

    slider->setRange(min, max);
    slider->setValue(current);
    // slider->setSingleStep(1);
    slider->setTickInterval(10);
    slider->setTickPosition(QSlider::TicksBothSides);

    input->setText(QString::number(current));
    input->setMaximumWidth(70);
    input->setValidator(new QIntValidator(min, max));

    list.push_back(slider);

    connect(slider, &QSlider::valueChanged, [input, slider, this]() -> void {
        input->setText(QString::number(slider->value()));
        this->submitChanges();
    });
    connect(input, &QLineEdit::textChanged, [input, slider, this]() -> void {
        slider->setValue(input->text().toInt());
        this->submitChanges();
    });

    grid->addWidget(sliderLabel, grid->rowCount(), 0);
    grid->addWidget(input, grid->rowCount() - 1, 5);
    grid->addWidget(slider, grid->rowCount() - 1, 6);
}