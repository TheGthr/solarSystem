#define _USE_MATH_DEFINES

#include "trackball.h"
#include <cmath>


// Constructeur
Trackball::Trackball(unsigned int w, unsigned int h, bool isOrtho, float distanceToCam)
{
    m_Width  = w;
    m_Height = h;

    m_IsOrtho = isOrtho;

    if(m_IsOrtho)
        m_DistanceToCam = distanceToCam;
    else
        m_DistanceToCam = 1000.0f * log(distanceToCam);

    UpdateMatrix();
}


// Conversion d'un point coordonnee ecran en point sur la sphere
QVector3D Trackball::ArcBallConvert(const QPoint & p) const
{
    QVector3D v((2.0f * p.x()) / m_Width - 1.0f, 1.0f - (2.0f * p.y()) / m_Height, 0.0f);

    // Calcul de la composante z
    float sqrZ = 1.0f - v.lengthSquared();

    if(sqrZ > 0.0f)
        v.setZ(sqrt(sqrZ));
    else
        v.normalize();

    return v;
}


// Fonction de mise a jour de la matrice
void Trackball::UpdateMatrix()
{
    QMatrix4x4 matrixToUpdate;
    matrixToUpdate.rotate(m_Quaternion);

    m_Matrix = matrixToUpdate;

    if(m_IsOrtho)
        m_Matrix(3, 3)  = m_DistanceToCam;
    else
        m_Matrix(2, 3) -= std::exp(m_DistanceToCam / 1000.0f) - 1.0f;
}


// Fonction a appeler quand la fenetre est redimensionnee
void Trackball::Resize(unsigned int w, unsigned int h)
{
    m_Width = w;
    m_Height = h;
}

// Fonction a appeler quand un bouton est presse
void Trackball::Press(const QPoint & point)
{
    m_Position = ArcBallConvert(point);
}


// Fonction a appeler quand un bouton est relache
void Trackball::Release(const QPoint & point)
{
    m_Position = ArcBallConvert(point);
}


// Fonction a appeler lors d'un zoom
void Trackball::Wheel(int delta)
{
    // Calcul du nouveau Z
    if(m_IsOrtho)
        m_DistanceToCam = qBound(1.0e-5f, m_DistanceToCam + 0.001f * delta, 100.0f);
    else
        m_DistanceToCam = qBound(0.0f, m_DistanceToCam + delta, 10000.0f);

    UpdateMatrix();
}


// Fonction a appeler lors d'un deplacement
void Trackball::Move(const QPoint & point)
{
    QVector3D vector = ArcBallConvert(point);

    // Calcul de l'axe de rotation et son angle
    QVector3D rotationAxis = QVector3D::crossProduct(m_Position, vector);
    m_Position = vector;

    float rotationAngle = asin(rotationAxis.length());
    rotationAxis.normalize();

    // Mise a jour du quaternion et de la matrice
    m_Quaternion = QQuaternion::fromAxisAndAngle(rotationAxis, 180.0f / M_PI * rotationAngle) * m_Quaternion;

    UpdateMatrix();
}


// Fonction d'acces a la matrice de transformation
const float * Trackball::GetMatrix() const
{
    return m_Matrix.constData();
}
