#ifndef __DRAWER_H
#define __DRAWER_H

#include <cmath>

#include "Object/Point3D.h"

class Drawer
{
public:
    virtual ~Drawer() = default;
    virtual void drawLine(const Point3D& a, const Point3D& b) = 0;

protected:
    Drawer(const size_t w, const size_t h) : w(w), h(h) { }
    const size_t w;
    const size_t h;
};

#endif // __DRAWER_H
