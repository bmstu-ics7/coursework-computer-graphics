#ifndef __PARTICLE_H
#define __PARTICLE_H

#include "VisibleObject.h"
#include "Point3D.h"

class Particle : public VisibleObject
{
public:
    Particle();
    Particle(double x, double y, double z);
    Particle(const Point3D& point);

    const Point3D& getPoint();
    Point3D getConstPoint();

private:
    Point3D point;
};

#endif // __PARTICLE_H
