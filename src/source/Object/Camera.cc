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

void Camera::rotate(GLfloat x, GLfloat y, GLfloat z)
{
    _rotateX += x;
    _rotateY += y;
    _rotateZ += z;
}
