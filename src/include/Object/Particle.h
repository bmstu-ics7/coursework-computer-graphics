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

    void draw(Drawer& drawer) override;
    void scale(const Point3D& center, double k) override;
    void offset(double dx, double dy, double dz) override;
    void rotateX(const Point3D& center, double a) override;
    void rotateY(const Point3D& center, double a) override;
    void rotateZ(const Point3D& center, double a) override;

    const Point3D& getPoint();
    Point3D getConstPoint();

private:
    Point3D point;
};

#endif // __PARTICLE_H
