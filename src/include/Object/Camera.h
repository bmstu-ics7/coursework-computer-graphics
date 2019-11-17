#ifndef __CAMERA_H
#define __CAMERA_H

//#include "UnvisibleObject.h"
#include "Math/Matrix.h"
#include "Point3D.h"

class Camera// : public UnvisibleObject
{
public:
    Camera();
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ);
    void setPosition(GLfloat posX, GLfloat posY, GLfloat posZ);
    void move(GLfloat x, GLfloat y, GLfloat z, GLfloat distance = 1);
    void scale(GLfloat x, GLfloat y, GLfloat z);
    void rotate(GLfloat x, GLfloat y, GLfloat z);
    Point3D multiplication(const Point3D& point);

    GLfloat offsetX = 0;
    GLfloat offsetY = 0;
    GLfloat offsetZ = 0;

    GLfloat scaleX = 1;
    GLfloat scaleY = 1;
    GLfloat scaleZ = 1;

    GLfloat rotateX = 0;
    GLfloat rotateY = 0;
    GLfloat rotateZ = 0;

private:
    Matrix mat;
    Matrix reverse;


private:
    void findReverse();
    void multiplicationMatrix(Matrix& matrix);
    Matrix matrixRotateX(GLfloat a);
    Matrix matrixRotateY(GLfloat a);
    Matrix matrixRotateZ(GLfloat a);
};

#endif // __CAMERA_H
