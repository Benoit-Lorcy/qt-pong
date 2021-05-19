#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H
#include <QtWidgets>

#include "configWindow.h"
#include "constants.h"
#include "view.h"

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
public:
    FenetrePrincipale();
    ~FenetrePrincipale();
    //QGroupBox* BuildGroupBoxControle();

public slots:

private:
    ConfigWindow* conf;
    QMenu* menuConfig;
    Scene* mainScene;
    View* mainView;
    //c'est surment pas la meilleure façon de forcer le ratio d'une fenetre mais c'est la meilleure que j'ai trouvé
    //c'est une réécriture de resizeEvent qui ne bloque la fenetre de s'agrandir par la hauteur si la hauteur n'est pas sufisante.
    //void resizeEvent(QResizeEvent* event)
    //{
    //float ratio = (float)this->width() / this->height();
    //le code commenté semble être une bonne idée mais ce n'est pas une bonne idée
    /*if (this->width() < this->height() * 1.71) 
        {
            this->resize(this->height() * 1.71, this->height());
        }*/
    //this->setMinimumWidth(this->height() * 1.706);
    //}
};

#endif