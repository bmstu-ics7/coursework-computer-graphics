#ifndef __ROTATECAMERA_H
#define __ROTATECAMERA_H

#include "Command.h"

class RotateCamera : Command
{
public:
    RotateCamera(double x, double y, double z, double angle)
        : x(x), y(y), z(z), angle(angle) { }
    void execute(Scene& facade) override;

private:
    double x;
    double y;
    double z;
    double angle;
};

#endif // __ROTATECAMERA_H
