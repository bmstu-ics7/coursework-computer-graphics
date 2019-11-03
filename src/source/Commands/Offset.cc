#include "Commands/Offset.h"

void Offset::execute(Scene& facade)
{
    TransformManager manager = facade.getTransformManager();
    PositionIterator beginP = facade.getObjects().find(begin);
    PositionIterator endP = facade.getObjects().find(end);
    manager.offset(begin, end, beginP, endP, dx, dy, dz);
}
