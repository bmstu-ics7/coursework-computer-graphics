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
    void moveLocal(GLfloat x, GLfloat y, GLfloat z, GLfloat distance = 1);
    void moveGlobal(GLfloat x, GLfloat y, GLfloat z, GLfloat distance = 1);
    void scale(GLfloat x, GLfloat y, GLfloat z);
    void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    Point3D multiplication(const Point3D& point);

private:
    Matrix mat;
    Matrix reverse;

private:
    void findReverse();
};

#endif // __CAMERA_H
