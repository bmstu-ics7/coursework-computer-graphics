#ifndef __PARTICLE_H
#define __PARTICLE_H

#include <QtOpenGL>

class Particle
{
public:
    Particle();
    Particle(GLdouble x, GLdouble y, GLdouble z);
    Particle(GLdouble x, GLdouble y, GLdouble z, GLdouble r, GLdouble g, GLdouble b);

    GLdouble x();
    GLdouble y();
    GLdouble z();

    GLdouble r();
    GLdouble g();
    GLdouble b();

    const GLdouble x() const;
    const GLdouble y() const;
    const GLdouble z() const;

    const GLdouble r() const;
    const GLdouble g() const;
    const GLdouble b() const;

private:
    GLdouble _x;
    GLdouble _y;
    GLdouble _z;

    GLdouble _r;
    GLdouble _g;
    GLdouble _b;
};

#endif // __PARTICLE_H
