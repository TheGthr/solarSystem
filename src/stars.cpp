#include "stars.h"

Stars::Stars()
{
    // Creation de la quadrique
    quad_ = gluNewQuadric();

    // Position aléatoire
    posX_ = -50 + static_cast <float> (rand())/(static_cast <float> (RAND_MAX/100));
    posY_ = -50 + static_cast <float> (rand())/(static_cast <float> (RAND_MAX/100));
    posZ_ = -50 + static_cast <float> (rand())/(static_cast <float> (RAND_MAX/100));
}

Stars::~Stars()
{
    // Destruction de la quadrique
    gluDeleteQuadric(quad_);
}

void Stars::Display() {
    glPushMatrix();
    glTranslatef(posX_, posY_, posZ_);

    GLfloat colorEtoile[] = {1.0,1.0,1.0,1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, colorEtoile);
    gluSphere(quad_, 0.15, 30, 30);
    glPopMatrix();
}
