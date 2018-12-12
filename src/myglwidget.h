#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "planet.h"
#include "stars.h"
#include "trackball.h"
#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>


// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    // Constructeur
    MyGLWidget(QWidget * parent = nullptr);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    GLuint processHits(GLint hits, GLuint selectBuff[]);

protected:
    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent * event);



private:
    // Timer d'animation
    float m_TimeElapsed { 0.0f };
    QTimer m_AnimationTimer;

    // Liste des planetes
    std::vector<Planet *> m_Planetes;

    // Liste des etoiles
    std::vector<Stars *> m_Etoiles;

    // Trackball pour la gestion de la camera
    Trackball m_Trackball;

    // Nom de la planete que l'on click
    QString *stringHit_;

    GLuint hitID_;
};

#endif // MYGLWIDGET_H
