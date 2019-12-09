#include "Widget/Widget.h"
#include <QDebug>

void Widget::setCamera()
{
    _camera.setToIdentity();
    _camera.translate(_translateX, _translateY, _translateZ);
    _camera.rotate(_angle);

    _shadowLightMatrix.setToIdentity();
    _shadowLightMatrix.rotate(_lightRotateX, 1.0, 0.0, 0.0);
    _shadowLightMatrix.rotate(_lightRotateY, 0.0, 1.0, 0.0);
    _shadowLightMatrix.rotate(_lightRotateZ, 0.0, 0.0, 1.0);

    _lightMatrix.setToIdentity();
    _lightMatrix.rotate(-_lightRotateZ, 0.0, 0.0, 1.0);
    _lightMatrix.rotate(-_lightRotateY, 0.0, 1.0, 0.0);
    _lightMatrix.rotate(-_lightRotateX, 1.0, 0.0, 0.0);
}

void Widget::translateCamera(GLfloat x, GLfloat y, GLfloat z)
{
    _translateX += x;
    _translateY += y;
    _translateZ += z;
}

void Widget::rotateCamera(QQuaternion angle)
{
    _angle *= angle;
}
