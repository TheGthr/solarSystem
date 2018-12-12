#ifndef STARS_H
#define STARS_H

#include <GL/glu.h>
#include <QColor>
#include <QGLWidget>
#include <QImage>

using namespace std;

class Stars
{
public:
    // Constructeur
    Stars();

    // Destructeur
    virtual ~Stars();

    // Methode d'affichage
    void Display();

private:
    GLUquadric*  quad_;
    float posX_;
    float posY_;
    float posZ_;
};

#endif // STARS_H
