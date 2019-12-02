#include "Widget/Widget.h"
#include <QDebug>

void Widget::setCamera()
{
    glTranslatef(_offsetX, _offsetY, _offsetZ);
    glScalef(_scaleX, _scaleY, _scaleZ);
    glRotatef(_rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(_rotateY, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotateZ, 0.0f, 0.0f, 1.0f);
}

void Widget::offsetCamera(GLdouble x, GLdouble y, GLdouble z)
{
    _offsetX += x;
    _offsetY += y;
    _offsetZ += z;
}

void Widget::scaleCamera(GLdouble k)
{
    _scaleX *= k;
    _scaleY *= k;
    _scaleZ *= k;
}

void Widget::rotateCamera(GLint x, GLint y, GLint z)
{
    _rotateX += x;
    _rotateX %= 360;

    _rotateY += y;
    _rotateY %= 360;

    _rotateZ += z;
    _rotateZ %= 360;
}
