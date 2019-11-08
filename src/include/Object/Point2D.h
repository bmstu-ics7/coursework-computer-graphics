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

    double x() const;
    double y() const;

private:
    double _x;
    double _y;
};

#endif // __POINT2D_H
