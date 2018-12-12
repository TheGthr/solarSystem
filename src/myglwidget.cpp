#define _USE_MATH_DEFINES

#include "myglwidget.h"
#include "planet.h"
#include <QApplication>
#include <QDesktopWidget>
#include <cmath>
#include <random>


// Declarations des constantes
const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;
const float MAX_DIMENSION     = 50.0f;


// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QGLWidget(parent), m_Trackball(WIN_WIDTH, WIN_HEIGHT, true, 1.0f)
{
    // Reglage de la taille/position
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    // Connexion du timer
    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
        m_TimeElapsed += 1.0f / 12.0f;
        updateGL();
    });

    m_AnimationTimer.setInterval(10);
    m_AnimationTimer.start();

    // On ini hitID pour pouvoir avoir une condition pour ne rien afficher tant que l'on n'a pas cliqué
    hitID_ = 10;
}


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);

    // Chargement des textures
    QImage tMercure = QGLWidget::convertToGLFormat(QImage(":/img/res/mercure.jpg"));
    QImage tVenus = QGLWidget::convertToGLFormat(QImage(":/img/res/venus.jpg"));
    QImage tTerre = QGLWidget::convertToGLFormat(QImage(":/img/res/terre.jpg"));
    QImage tMars = QGLWidget::convertToGLFormat(QImage(":/img/res/mars.jpg"));
    QImage tJupiter = QGLWidget::convertToGLFormat(QImage(":/img/res/jupiter.jpg"));
    QImage tSaturne = QGLWidget::convertToGLFormat(QImage(":/img/res/saturne.jpg"));
    QImage tUranus = QGLWidget::convertToGLFormat(QImage(":/img/res/uranus.jpg"));
    QImage tNeptune = QGLWidget::convertToGLFormat(QImage(":/img/res/neptune.jpg"));
    QImage tLune = QGLWidget::convertToGLFormat(QImage(":/img/res/lune.jpg"));
    QImage tSoleil = QGLWidget::convertToGLFormat(QImage(":/img/res/soleil.jpg"));

    GLuint* m_TextureID = new GLuint[10];
    glGenTextures(10, m_TextureID);

    // On charge la place des textures dans le vecteur m_TextureID
    // Pour pouvoir les identifier dans Planet par la suite
    glBindTexture(GL_TEXTURE_2D, m_TextureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tMercure.width(),tMercure.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tMercure.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, m_TextureID[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tVenus.width(),tVenus.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tVenus.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, m_TextureID[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tTerre.width(),tTerre.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tTerre.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, m_TextureID[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tMars.width(),tMars.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tMars.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, m_TextureID[4]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tJupiter.width(),tJupiter.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tJupiter.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, m_TextureID[5]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tSaturne.width(),tSaturne.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tSaturne.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, m_TextureID[6]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tUranus.width(),tUranus.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tUranus.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, m_TextureID[7]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tNeptune.width(),tNeptune.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tNeptune.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, m_TextureID[8]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tLune.width(),tLune.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tLune.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, m_TextureID[9]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tSoleil.width(),tSoleil.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tSoleil.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // distance par rapport au soleil | rayon | periode de rotation | periode de révolution
    // Ajout des planetes dans le vecteur m_Planetes
    m_Planetes.push_back(new Planet("Mercure", 0, 7.5f, 0.5f, 58.646f, 87.969f, 200.0f, 248.0f, 242.0f, m_TextureID[0]));
    m_Planetes.push_back(new Planet("Venus", 1, 10.0f, 0.90f, -243.018f, 224.701f, 255.0f, 255.0f, 242.0f, m_TextureID[1]));
    m_Planetes.push_back(new Planet("Terre", 2, 13.0f, 0.90f, 0.997f, 365.256f, 211.0f, 192.0f, 227.0f, m_TextureID[2]));
    m_Planetes.push_back(new Planet("Mars", 3, 17.5f, 1.50f, 1.025f, 686.960f, 247.0f, 115.0f, 12.0f, m_TextureID[3]));
    m_Planetes.push_back(new Planet("Jupiter", 4, 27.0f, 3.00f, 0.413f, 935.354f, 253.0f, 199.0f, 145.0f, m_TextureID[4]));
    m_Planetes.push_back(new Planet("Saturne", 5, 35.0f, 2.50f, 0.448f, 1757.736f, 200.0f, 196.0f, 251.0f, m_TextureID[5]));
    m_Planetes.push_back(new Planet("Uranus", 6, 40.5f, 1.50f, -0.718f, 3687.150f, 198.0f, 241.0f, 245.0f, m_TextureID[6]));
    m_Planetes.push_back(new Planet("Neptune", 7, 45.0f, 1.50f, 0.671f, 6224.903f, 57.0f, 182.0f, 247.0f, m_TextureID[7]));
    m_Planetes.push_back(new Planet("Soleil", 8, 0.0f, 5.0f, 9999.0f, 9999.0f, 240.0f, 198.0f, 29.0f, m_TextureID[9]));

    // Etoiles
    for(int i = 0; i < 50; i++) {
        m_Etoiles.push_back(new Stars());
    }

    // Reglage de la lampe
    glEnable(GL_LIGHT0);
    GLfloat color_ambiant[] = {1.0,1.0,1.0,1.0};
    // On met une lampe ambiante ET diffuse pour avoir un bon éclairage
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, color_ambiant);
    GLfloat pos[] = {0.0f,0.0f,0.0f,1.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,pos);

    // Activation de la lumiere
    glEnable(GL_LIGHTING);
}


// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);

    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(width != 0)
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * height / static_cast<float>(width), MAX_DIMENSION * height / static_cast<float>(width), -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Fonction d'affichage
void MyGLWidget::paintGL()
{
    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Definition de la position de la camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,-3,10,0,0,0,0,1,0);

    // Mise a jour du trackball
    glMultMatrixf(m_Trackball.GetMatrix());

    // Affichage des m_Planetes
    for(int i = 0; i < m_Planetes.size(); i++)
        m_Planetes[i]->Display(m_TimeElapsed);

    for(int i = 0; i < m_Etoiles.size(); i++)
        m_Etoiles[i]->Display();

    QString *daysElapsedStr = new QString("Time elapsed : " + QString::number(int(m_TimeElapsed), 10) + " hours");
    renderText(30, 30, *daysElapsedStr);
    //QString *planetStr = new ;
    if(hitID_ >= 10) {
        renderText(50, 50, QString::fromStdString(" ")); // On ne veut rien afficher tant que l'on n'a rien cliqué
        // ou que l'on clique à côté d'une planète
    } else {
        QString *str = new QString(QString::number(hitID_));
        // Si je n'avais plus eu de bug : QString *str = new QString(QString::fromStdString(m_Planetes[hitID_]->getName()));
        renderText(50, 50, *str);
    }
}


// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
        // Activation/Arret de l'animation
        case Qt::Key_Space:
        {
            if(m_AnimationTimer.isActive())
                m_AnimationTimer.stop();
            else
                m_AnimationTimer.start();

            break;
        }

        // Sortie de l'application
        case Qt::Key_Escape:
        {
            exit(0);
        }

        // Cas par defaut
        default:
        {
            // Ignorer l'evenement
            event->ignore();
            return;
        }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();
}

// Fonctions de gestion d'interactions souris
void MyGLWidget::mousePressEvent(QMouseEvent * event)
{
    // Gestion du click droit
    if(event->buttons() & Qt::RightButton)
    {
        m_Trackball.Press(event->pos());
        updateGL();
        event->accept();
    }

    // Gestion du click gauche
    if(event->button() ==  Qt::LeftButton)
    {
        GLint hits;
        GLuint selectBuff[512];
        glSelectBuffer(512, selectBuff);

        glRenderMode(GL_SELECT);
        glInitNames();
        glPushName(0);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        gluPickMatrix(event->x(), (viewport[3] - event->y()), 2.0, 2.0, viewport);
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * height() / static_cast<float>(width()), MAX_DIMENSION * height() / static_cast<float>(width()), -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);
        glPopMatrix();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0,-3,10,0,0,0,0,1,0);

        for(int i = 0; i < m_Planetes.size(); i++) {
            glLoadName(i);
            m_Planetes[i]->Display(m_TimeElapsed);
        }
        glFlush();

        hits = glRenderMode(GL_RENDER);
        hitID_ = processHits(hits, selectBuff);
    }
}


void MyGLWidget::mouseReleaseEvent(QMouseEvent * event)
{
    // Gestion du click droit
    if(event->button() ==  Qt::RightButton)
    {
        m_Trackball.Release(event->pos());
        updateGL();
        event->accept();
    }
}


void MyGLWidget::wheelEvent(QWheelEvent * event)
{
    m_Trackball.Wheel(event->delta());
    updateGL();
    event->accept();
}


void MyGLWidget::mouseMoveEvent(QMouseEvent * event)
{
    // Gestion du click droit
    if(event->buttons() & Qt::RightButton)
    {
        m_Trackball.Move(event->pos());
        updateGL();
        event->accept();
    }
}

GLuint MyGLWidget::processHits(GLint hits, GLuint selectBuff[]) {
    GLuint closestID = 0xfffffff;
    float closestZ = 0xfffffff;
    for(long ii = 0, h = 0; ii < hits; ii++) {
        GLuint nbNames = selectBuff[h++];
        GLuint zmin = selectBuff[h++];
        ++h;
        h += nbNames;
        if(zmin < closestZ) {
            closestZ = zmin;
            closestID = selectBuff[h-1];
        }
    }
    return closestID;
}
