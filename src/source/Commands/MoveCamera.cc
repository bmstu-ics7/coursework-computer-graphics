#include "Commands/MoveCamera.h"

void MoveCamera::execute(Scene& facade)
{
    switch(action) {
    case Forward:
    case Back:
        facade.getMatrix().scale(x, y, z);
        break;
    case Up:
    case Down:
    case Left:
    case Right:
        facade.getMatrix().moveGlobal(x, y, z, distance);
        break;
    }
}
