#include "Object/Point2D.h"

Point2D::Point2D() : Point2D(0) { }

Point2D::Point2D(double x) : Point2D(x, x) { }

Point2D::Point2D(double x, double y)
    : _x(x), _y(y) { }

Point2D::Point2D(const Point3D& point)
{
    _x = int(point.x());
    _y = int(point.y());
}

double Point2D::x() const
{
    return _x;
}

double Point2D::y() const
{
    return _y;
}
