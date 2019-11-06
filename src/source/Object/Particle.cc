#include "Object/Particle.h"

Particle::Particle() : 
    Particle(Point3D()) { }

Particle::Particle(double x, double y, double z)
    : Particle(Point3D(x, y, z)) { }

Particle::Particle(const Point3D& point)
    : VisibleObject()
{
    this->point = point;
}

const Point3D& Particle::getPoint()
{
    return point;
}

Point3D Particle::getConstPoint()
{
    return point;
}
