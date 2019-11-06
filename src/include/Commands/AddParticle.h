#include "Command.h"

class AddParticle : Command
{
public:
    AddParticle(double x, double y, double z)
        : _x(x), _y(y), _z(z) { }
    void execute(Scene& facade) override;

private:
    double _x;
    double _y;
    double _z;
};
