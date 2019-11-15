#ifndef __ROTATECAMERA_H
#define __ROTATECAMERA_H

#include "Command.h"

class RotateCamera : Command
{
public:
    RotateCamera(double x, double y, double z)
        : x(x), y(y), z(z) { }
    void execute(Scene& facade) override;

private:
    double x;
    double y;
    double z;
};

#endif // __ROTATECAMERA_H
