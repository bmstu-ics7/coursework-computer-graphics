#include "Object/Camera.h"
#include <QDebug>

void Camera::move(GLfloat x, GLfloat y, GLfloat z, GLfloat distance)
{
    _offsetX += x * distance;
    _offsetY += y * distance;
    _offsetZ += z * distance;
}

void Camera::scale(GLfloat x, GLfloat y, GLfloat z)
{
    _scaleX *= x;
    _scaleY *= y;
    _scaleZ *= z;
}

void Camera::rotate(GLint x, GLint y, GLint z)
{
    _rotateX += x;
    _rotateY += y;
    _rotateZ += z;

    _rotateX %= 360;
    _rotateY %= 360;
    _rotateZ %= 360;
}
