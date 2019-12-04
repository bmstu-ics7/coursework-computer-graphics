#include "Objects/Particle.h"

Particle::Particle() :
    Particle(0.0, 0.0, 0.0) { }

Particle::Particle(GLdouble x, GLdouble y, GLdouble z)
    : Particle(x, y, z, 1.0, 1.0, 1.0) { }

Particle::Particle(GLdouble x, GLdouble y, GLdouble z, GLdouble r, GLdouble g, GLdouble b)
    : _x(x), _y(y), _z(z), _r(r), _g(g), _b(b) { }

GLdouble Particle::x() { return _x; }
GLdouble Particle::y() { return _y; }
GLdouble Particle::z() { return _z; }

GLdouble Particle::r() { return _r; }
GLdouble Particle::g() { return _g; }
GLdouble Particle::b() { return _b; }

const GLdouble Particle::x() const { return _x; }
const GLdouble Particle::y() const { return _y; }
const GLdouble Particle::z() const { return _z; }

const GLdouble Particle::r() const { return _r; }
const GLdouble Particle::g() const { return _g; }
const GLdouble Particle::b() const { return _b; }
