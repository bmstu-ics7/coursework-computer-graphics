#include "Object/Position.h"

Position::Position(double x, double y, double z)
    : Position(Point3D(x, y, z)) { }

Position::Position(Point3D center) : center(center) { }

Position::Position(const std::vector< Point3D >& points)
{
    double sumX = 0;
    double sumY = 0;
    double sumZ = 0;

    for (Point3D point : points) {
        sumX += point.getX();
        sumY += point.getY();
        sumZ += point.getZ();
    }

    center = Point3D(sumX / points.size(),
                     sumY / points.size(),
                     sumZ / points.size());
}

void Position::offset(double dx, double dy, double dz)
{
    center.offset(dx, dy, dz);
}

Point3D Position::get()
{
    return center;
}
