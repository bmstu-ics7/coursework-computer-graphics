#include "Object/Particle.h"

Particle::Particle() :
    Particle(Point3D()) { }

Particle::Particle(double x, double y, double z)
    : Particle(Point3D(x, y, z)) { }

Particle::Particle(const Point3D& point)
    : Particle(point, 1.0, 1.0, 1.0) { }

Particle::Particle(double x, double y, double z, double r, double g, double b)
    : Particle(Point3D(x, y, z), r, g, b) { }

Particle::Particle(const Point3D& point, double r, double g, double b)
    : VisibleObject(), _point(point), _r(r), _g(g), _b(b) { }

const Point3D& Particle::point()
{
    return _point;
}

Point3D Particle::constPoint()
{
    return _point;
}

void Particle::draw(Drawer& drawer)
{
    drawer.drawParticle(_point, _r, _g, _b);
}

void Particle::scale(const Point3D& center, double k)
{
    _point.scale(center, k);
}

void Particle::offset(double dx, double dy, double dz)
{
    _point.offset(dx, dy, dz);
}

void Particle::rotateX(const Point3D& center, double a)
{
    _point.rotateX(center, a);
}

void Particle::rotateY(const Point3D& center, double a)
{
    _point.rotateY(center, a);
}

void Particle::rotateZ(const Point3D& center, double a)
{
    _point.rotateZ(center, a);
}
