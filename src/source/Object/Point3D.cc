#include "Object/Point3D.h"

Point3D::Point3D() : Point3D(0) { }

Point3D::Point3D(double x) : Point3D(x, x, x) { }

Point3D::Point3D(double x, double y, double z)
    : _x(x), _y(y), _z(z) { }

void Point3D::scale(const Point3D& center, double k)
{
    _x = scaleOne(_x, center._x, k);
    _y = scaleOne(_y, center._y, k);
    _z = scaleOne(_z, center._z, k);
}

double Point3D::scaleOne(double coord, double center, double k)
{
    return center + (coord - center) * k;
}

void Point3D::offset(double dx, double dy, double dz)
{
    _x += dx;
    _y += dy;
    _z += dz;
}

void Point3D::rotateX(const Point3D& center, double a)
{
    double ax = (a * M_PI) / 180.0;

    double cy = center._y;
    double cz = center._z;

    Point3D p = *this;
    _y = cy + (p._y - cy) * cos(ax) + (p._z - cz) * sin(ax);
    _z = cz - (p._y - cy) * sin(ax) + (p._z - cz) * cos(ax);
}

void Point3D::rotateY(const Point3D& center, double a)
{
    double ay = (a * M_PI) / 180.0;

    double cx = center._x;
    double cz = center._z;

    Point3D p = *this;
    _x = cx + (p._z - cz) * sin(ay) + (p._x - cx) * cos(ay);
    _z = cz + (p._z - cz) * cos(ay) - (p._x - cx) * sin(ay);
}

void Point3D::rotateZ(const Point3D& center, double a)
{
    double az = (a * M_PI) / 180.0;

    double cx = center._x;
    double cy = center._y;

    Point3D p = *this;
    _x = cx + (p._x - cx) * cos(az) + (p._y - cy) * sin(az);
    _y = cy - (p._x - cx) * sin(az) + (p._y - cy) * cos(az);
}

double Point3D::x() const
{
    return _x;
}

double Point3D::y() const
{
    return _y;
}

double Point3D::z() const
{
    return _z;
}
