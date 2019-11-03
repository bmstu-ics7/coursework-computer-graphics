#include "Object/Camera.h"
#include <QDebug>

Camera::Camera() : Camera(0.0f, 0.0f, 0.0f) { }

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ)
    : UnvisibleObject()
{
    mat = Matrix(4);

    setPosition(posX, posY, posZ);

    mat[0][0] = 1.0f;
    mat[1][1] = 1.0f;
    mat[2][2] = 1.0f;
    mat[3][3] = 1.0f;
}


void Camera::setPosition(GLfloat posX, GLfloat posY, GLfloat posZ)
{
    mat[0][3] = -posX;
    mat[1][3] = -posY;
    mat[2][3] = -posZ;
}

void Camera::moveLocal(GLfloat x, GLfloat y, GLfloat z, GLfloat distance)
{
    GLfloat dx = x * mat[0][0] + y * mat[0][1] + z * mat[0][2];
    GLfloat dy = x * mat[1][0] + y * mat[1][1] + z * mat[1][2];
    GLfloat dz = x * mat[2][0] + y * mat[2][1] + z * mat[2][2];

    mat[0][3] += dx * distance;
    mat[1][3] += dy * distance;
    mat[2][3] += dz * distance;
}

void Camera::moveGlobal(GLfloat x, GLfloat y, GLfloat z, GLfloat distance)
{
    mat[0][3] += x * distance;
    mat[1][3] += y * distance;
    mat[2][3] += z * distance;
}

void Camera::rotateGlobal(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat dx = x * mat[0][0] + y * mat[0][1] + z * mat[0][2];
    GLfloat dy = x * mat[1][0] + y * mat[1][1] + z * mat[1][2];
    GLfloat dz = x * mat[2][0] + y * mat[2][1] + z * mat[2][2];
}
