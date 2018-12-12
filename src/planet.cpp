#include "planet.h"

using namespace std;

Planet::Planet(string name, unsigned int ID, float pos, float r, float tRot, float tRev, float colorR, float colorG, float colorB, GLuint m_TextureID)
{
    // Initialisation des paramètres
    pos_ = pos;
    name_ = name;
    r_ = r;
    tRot_ = tRot;
    tRev_ = tRev;
    m_TextureID_ = m_TextureID;
    color_[0] = colorR/255.0f;
    color_[1] = colorG/255.0f;
    color_[2] = colorB/255.0f;
    // Creation de la quadrique
    quad_ = gluNewQuadric();

    // Identificateur
    ID_ = ID;
}


Planet::~Planet()
{
    // Destruction de la quadrique
    gluDeleteQuadric(quad_);
}


void Planet::Display(const float timeInDays) const
{
    glPushMatrix();

    // Transformations pour la periode de revolution
    // On fait une projection sur les axes
    glTranslatef(pos_*cos(timeInDays*2*3.14/tRev_), pos_*sin(timeInDays*2*3.14/tRev_), 0);

    // Transformation pour la periode de rotation
    glRotatef(2*3.14*timeInDays/tRot_, 0, 0, 1);

    if(name_ == "Soleil") {
        GLfloat colorSol[] = {1.0,1.0,0.0,1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, colorSol);
    } else {
        GLfloat colorOther[] = {0.0,0.0,0.0,1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, colorOther);
    }
    // Couleur de l'objet
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, color_); // On définit la couleur courante
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_TextureID_);
    gluQuadricTexture(quad_, GL_TRUE);
    // Affichage de la quadrique
    gluSphere(quad_, r_, 30, 30);

    // Affichage de la lune pour la Terre
    if (name_ == "Terre") {
        glBindTexture(GL_TEXTURE_2D, 9);
        glTranslatef(1.5f*cos(timeInDays*2*3.14/27), 1.5f*sin(timeInDays*2*3.14/27), 0);
        float colorLune[] = {0.4,0.4,0.4};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colorLune);
        gluSphere(quad_, r_/2, 30, 30);
    }

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Création des traces des orbites
    // On ne réinitialise pas la couleur pour que chaque planète
    // ait une couleur d'orbite proche de sa vraie couleur
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 100; i++) {
        const float angle = (2*3.14159*i)/100;
        glVertex2f(pos_*cos(angle), pos_*sin(angle));
    }
    glEnd();
}

string Planet::getName() {
    return name_;
}

int Planet::getID() {
    return ID_;
}
