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

void Particle::draw(Drawer& drawer)
{
    drawer.drawParticle(point);
}

void Particle::scale(const Point3D& center, double k)
{
    point.scale(center, k);
}

void Particle::offset(double dx, double dy, double dz)
{
    point.offset(dx, dy, dz);
}

void Particle::rotateX(const Point3D& center, double a)
{
    point.rotateX(center, a);
}

void Particle::rotateY(const Point3D& center, double a)
{
    point.rotateY(center, a);
}

void Particle::rotateZ(const Point3D& center, double a)
{
    point.rotateZ(center, a);
}
