#include "Object/Point2D.h"

Point2D::Point2D() : Point2D(0) { }

Point2D::Point2D(double x) : Point2D(x, x) { }

Point2D::Point2D(double x, double y)
{
    this->x = x;
    this->y = y;
}

Point2D::Point2D(const Point3D& point)
{
    x = int(point.getX());
    y = int(point.getY());
}

double Point2D::getX() const
{
    return x;
}

double Point2D::getY() const
{
    return y;
}
