#ifndef __OBJECT_H
#define __OBJECT_H

#include "Drawing/Drawer.h"

class Object
{
public:
    Object() { }

    bool isVisible() { return visible; }
    bool isCompose() { return compose; }

    virtual void draw(Drawer& drawer) = 0;
    virtual void scale(const Point3D& center, double k) = 0;
    virtual void offset(double dx, double dy, double dz) = 0;
    virtual void rotateX(const Point3D& center, double a) = 0;
    virtual void rotateY(const Point3D& center, double a) = 0;
    virtual void rotateZ(const Point3D& center, double a) = 0;

protected:
    bool visible;
    bool compose;
};

#endif // __OBJECT_H
