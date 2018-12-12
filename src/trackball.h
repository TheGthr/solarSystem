#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <QMatrix4x4>


// Classe dediee a la gestion du trackball
class Trackball
{
public:

    // Constructeur
    Trackball(unsigned int w, unsigned int h, bool isOrtho = false, float distanceToCam = 2.5f);

    // Fonction a appeler quand la fenetre est redimensionnee
    void Resize(unsigned int w, unsigned int h);

    // Fonction a appeler quand un bouton est presse
    void Press(const QPoint & point);

    // Fonction a appeler quand un bouton est relache
    void Release(const QPoint & point);

    // Fonction a appeler lors d'un zoom
    void Wheel(int delta);

    // Fonction a appeler lors d'un deplacement
    void Move(const QPoint & point);

    // Fonction d'acces a la matrice de transformation
    const float * GetMatrix() const;


private:

    // Dimensions de la fenetre
    unsigned int m_Width, m_Height;

    // Type de projection
    bool m_IsOrtho;

    // Derniere position connue
    QVector3D m_Position;

    // Eloignement de la camera
    float m_DistanceToCam;

    // Quaternion/Matrice correspondant a la rotation
    QQuaternion m_Quaternion;
    QMatrix4x4 m_Matrix;

    // Conversion d'un point coordonnee ecran en point sur la sphere
    QVector3D ArcBallConvert(const QPoint & p) const;

    // Fonction de mise a jour de la matrice
    void UpdateMatrix();
};

#endif // TRACKBALL_H
