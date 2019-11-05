#ifndef __PARTICLE_H
#define __PARTICLE_H

class Particle : public VisibleObject
{
public:
    Particle();
    Particle(const Point3D& point);

private:
    Point3D point;
};

#endif // __PARTICLE_H
