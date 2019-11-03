#include "Object/Point3D.h"

Point3D::Point3D() : Point3D(0) { }

Point3D::Point3D(double x) : Point3D(x, x, x) { }

Point3D::Point3D(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Point3D::scale(const Point3D& center, double k)
{
    x = scaleOne(x, center.x, k);
    y = scaleOne(y, center.y, k);
    z = scaleOne(z, center.z, k);
}

double Point3D::scaleOne(double coord, double center, double k)
{
    return center + (coord - center) * k;
}

void Point3D::offset(double dx, double dy, double dz)
{
    x += dx;
    y += dy;
    z += dz;
}

void Point3D::rotateX(const Point3D& center, double a)
{
    double ax = (a * M_PI) / 180.0;

    double cy = center.y;
    double cz = center.z;

    Point3D p = *this;
    y = cy + (p.y - cy) * cos(ax) + (p.z - cz) * sin(ax);
    z = cz - (p.y - cy) * sin(ax) + (p.z - cz) * cos(ax);
}

void Point3D::rotateY(const Point3D& center, double a)
{
    double ay = (a * M_PI) / 180.0;

    double cx = center.x;
    double cz = center.z;

    Point3D p = *this;
    x = cx + (p.z - cz) * sin(ay) + (p.x - cx) * cos(ay);
    z = cz + (p.z - cz) * cos(ay) - (p.x - cx) * sin(ay);
}

void Point3D::rotateZ(const Point3D& center, double a)
{
    double az = (a * M_PI) / 180.0;

    double cx = center.x;
    double cy = center.y;

    Point3D p = *this;
    x = cx + (p.x - cx) * cos(az) + (p.y - cy) * sin(az);
    y = cy - (p.x - cx) * sin(az) + (p.y - cy) * cos(az);
}

double Point3D::getX() const
{
    return x;
}

double Point3D::getY() const
{
    return y;
}

double Point3D::getZ() const
{
    return z;
}
