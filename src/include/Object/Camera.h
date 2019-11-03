#ifndef __CAMERA_H
#define __CAMERA_H

#include "UnvisibleObject.h"
#include "Math/Matrix.h"

class Camera : public UnvisibleObject
{
public:
    Camera();
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ);
    void setPosition(GLfloat posX, GLfloat posY, GLfloat posZ);
    void moveLocal(GLfloat x, GLfloat y, GLfloat z, GLfloat distance = 1);
    void moveGlobal(GLfloat x, GLfloat y, GLfloat z, GLfloat distance = 1);
    void rotateGlobal(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

private:
    Matrix mat;
};

#endif // __CAMERA_H
