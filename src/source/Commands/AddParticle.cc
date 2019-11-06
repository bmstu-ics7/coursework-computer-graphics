#include "Commands/AddParticle.h"

void AddParticle::execute(Scene& facade)
{
    std::shared_ptr< Particle > particle;
    particle.reset(new Particle(_x, _y, _z));
    facade.getObjects().add(particle);
}