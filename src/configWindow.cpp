#include "include/configWindow.h"

ConfigWindow::ConfigWindow() : QWidget() {
    // initialisation
    this->setMinimumWidth(100);
    this->setMinimumHeight(750);

    // Grid qui permet d'organiser les groupBoxes
    grid = new QGridLayout();
    grid->addWidget(createBalleGroup(), 0, 0);
    grid->addWidget(createPaddlesGroup(), 1, 0);
    grid->addWidget(createSceneGroup(), 2, 0);

    // Boutton reset
    QPushButton *maboi = new QPushButton(tr("Reset"));
    connect(maboi, &QPushButton::clicked, this, [this]() { this->reset(); });

    grid->addWidget(maboi, 3, 0);
    this->setLayout(grid);
}

// Groupe qui gère les variables des Balles
QGroupBox *ConfigWindow::createBalleGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Balle"));
    QGridLayout *grid = new QGridLayout;

    addCustomSlider("Largeur", grid, BALL_WIDTH, 10, 400, ballList);
    addCustomSlider("Hauteur", grid, BALL_HEIGHT, 10, 400, ballList);
    addCustomSlider("Vitesse", grid, BALL_BASE_SPEED, 5, 30, ballList);
    addCustomSlider("Acceleration", grid, BALL_INCREMENT_SPEED, 1, 100,
                    ballList);
    groupBox->setLayout(grid);

    return groupBox;
}

// Groupe qui gère les variables des Paddles
QGroupBox *ConfigWindow::createPaddlesGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Paddle"));
    QGridLayout *grid = new QGridLayout;

    addCustomSlider("Largeur", grid, PADDLE_WIDTH, 1, 100, paddlesList);
    addCustomSlider("Hauteur", grid, PADDLE_HEIGHT, 1, 500, paddlesList);
    addCustomSlider("Distance", grid, PADDLE_DISTANCE, 1, 200, paddlesList);
    addCustomSlider("Vitesse", grid, PADDLE_SPEED, 1, 50, paddlesList);
    groupBox->setLayout(grid);

    return groupBox;
}

// Groupe qui gère les variables de la scene
QGroupBox *ConfigWindow::createSceneGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Scene"));
    QGridLayout *grid = new QGridLayout;

    addCustomSlider("Taille texte", grid, TEXT_SIZE, 1, 16, sceneList);
    addCustomSlider("Score gagner", grid, SCORE_TO_WIN, 1, 20, sceneList);
    addCustomSlider("Volume", grid, AUDIO_VOLUME, 1, 100, sceneList);
    groupBox->setLayout(grid);

    return groupBox;
}

// Envoi les information des différentes listes de slider aux classes concernée
// Ce n'est pas très optimiser j'aurais préféré faire une fonction pour chaque
// emit mais ce n'est pas réalisable simplement
void ConfigWindow::submitChanges() {
    emit ballSettings(ballList[0]->value(), ballList[1]->value(),
                      ballList[2]->value(), ballList[3]->value());
    emit paddlesSettings(paddlesList[0]->value(), paddlesList[1]->value(),
                         paddlesList[2]->value(), paddlesList[3]->value());
    emit sceneSettings(sceneList[0]->value(), sceneList[1]->value(),
                       sceneList[2]->value());
}

// Permet de créer des slider qui sont réliés à un input pour faciliter la prise
// en main
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

// Réinitialisation les valeurs grâces au constants.h
void ConfigWindow::reset() {
    ballList[0]->setValue(BALL_WIDTH);
    ballList[1]->setValue(BALL_HEIGHT);
    ballList[2]->setValue(BALL_BASE_SPEED);
    ballList[3]->setValue(BALL_INCREMENT_SPEED);
    paddlesList[0]->setValue(PADDLE_WIDTH);
    paddlesList[1]->setValue(PADDLE_HEIGHT);
    paddlesList[2]->setValue(PADDLE_DISTANCE);
    paddlesList[3]->setValue(PADDLE_SPEED);
    sceneList[0]->setValue(TEXT_SIZE);
    sceneList[1]->setValue(SCORE_TO_WIN);
    sceneList[2]->setValue(AUDIO_VOLUME);
}