#ifndef __CAMERA_H
#define __CAMERA_H

#include "Math/Matrix.h"
#include "Point3D.h"

class Camera
{
public:
    Camera() { }
    void move(GLfloat x, GLfloat y, GLfloat z, GLfloat distance = 1);
    void scale(GLfloat x, GLfloat y, GLfloat z);
    void rotate(GLint x, GLint y, GLint z);

    GLfloat offsetX() { return _offsetX; }
    GLfloat offsetY() { return _offsetY; }
    GLfloat offsetZ() { return _offsetZ; }

    GLfloat scaleX() { return _scaleX; }
    GLfloat scaleY() { return _scaleY; }
    GLfloat scaleZ() { return _scaleZ; }

    GLint rotateX() { return _rotateX; }
    GLint rotateY() { return _rotateY; }
    GLint rotateZ() { return _rotateZ; }

private:
    GLfloat _offsetX = 0;
    GLfloat _offsetY = 0;
    GLfloat _offsetZ = 0;

    GLfloat _scaleX = 1;
    GLfloat _scaleY = 1;
    GLfloat _scaleZ = 1;

    GLint _rotateX = 0;
    GLint _rotateY = 0;
    GLint _rotateZ = 0;
};

#endif // __CAMERA_H
