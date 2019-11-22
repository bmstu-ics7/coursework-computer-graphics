#include "Commands/RotateCamera.h"

void RotateCamera::execute(Scene& facade)
{
    facade.getMatrix().rotate(x, y, z);
}
