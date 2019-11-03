#ifndef __POSITION_H
#define __POSITION_H

#include "Point3D.h"

class Position
{
public:
    Position(Point3D center);
    Position(const std::vector< Point3D >& points);
    void offset(double dx, double dy, double dz);
    Point3D get();

private:
    Point3D center;
};

#endif // __POSITION_H
