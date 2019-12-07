#include "Widget/Widget.h"
#include <QDebug>

void Widget::setCamera()
{
    _camera.setToIdentity();
    //_camera.scale(_scale, _scale, _scale);
    _camera.rotate(_angle);
    _camera.translate(_translateX, _translateY, _translateZ);
}

void Widget::translateCamera(GLfloat x, GLfloat y, GLfloat z)
{
    _translateX += x;
    _translateY += y;
    _translateZ += z;
}

void Widget::scaleCamera(GLfloat k)
{
    _scale *= k;
}

void Widget::rotateCamera(QQuaternion angle)
{
    _angle *= angle;
}
