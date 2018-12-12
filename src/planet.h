#ifndef PLANET_H
#define PLANET_H

#include <GL/glu.h>
#include <QColor>
#include <QGLWidget>
#include <QImage>

using namespace std;
// Classe dediee pour la gestion d'une planete
class Planet
{
public:
    // Constructeur avec parametres
    Planet(string name, unsigned int ID, float pos, float r, float tRot, float tRev, float colorR, float colorG, float colorB, GLuint m_TextureID);

    // Destructeur
    virtual ~Planet();

    // Methode d'affichage
    void Display(const float timeInDays) const;
    string getName();
    int getID();

private:
    // Paramètres
    GLUquadric*  quad_;
    string name_;
    float pos_;
    float r_;
    float tRot_;
    float tRev_;
    float color_[3];
    GLuint m_TextureID_;
    float posEtoileX_;
    float posEtoileY_;
    float posEtoileZ_;
    unsigned int ID_;
};


#endif // PLANET_H
