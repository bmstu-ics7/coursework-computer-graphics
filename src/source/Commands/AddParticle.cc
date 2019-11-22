#include "Commands/AddParticle.h"

void AddParticle::execute(Scene& facade)
{
    std::shared_ptr< Particle > particle;
    particle.reset(new Particle(_x, _y, _z, _r, _g, _b));
    facade.getObjects().add(particle);

    std::shared_ptr< Position > pos;
    pos.reset(new Position(0, 0, 0));
    facade.getObjects().addPosition(pos);
}
