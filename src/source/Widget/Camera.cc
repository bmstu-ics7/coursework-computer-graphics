#include "Widget/Widget.h"
#include <QDebug>

void Widget::setCamera()
{
    _camera.setToIdentity();
    _camera.translate(_translateX, _translateY, _translateZ);
    _camera.rotate(_angle);
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
