#include "Command.h"

class AddParticle : Command
{
public:
    AddParticle(double x, double y, double z)
        : AddParticle(x, y, z, 1.0, 1.0, 1.0) { }

    AddParticle(double x, double y, double z, double r, double g, double b)
        : _x(x), _y(y), _z(z), _r(r), _g(g), _b(b) { }
    void execute(Scene& facade) override;

private:
    double _x;
    double _y;
    double _z;

    double _r;
    double _g;
    double _b;
};
