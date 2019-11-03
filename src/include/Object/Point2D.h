#ifndef __POINT2D_H
#define __POINT2D_H

#include "Point3D.h"

class Point2D
{
public:
    Point2D();
    Point2D(double x);
    Point2D(double x, double y);
    Point2D(const Point3D& point);

    double getX() const;
    double getY() const;

private:
    double x;
    double y;
};

#endif // __POINT2D_H
