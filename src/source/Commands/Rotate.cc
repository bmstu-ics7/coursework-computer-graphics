#include "Commands/Rotate.h"

void Rotate::execute(Scene& facade)
{
    TransformManager manager = facade.getTransformManager();
    PositionIterator beginP = facade.getObjects().find(begin);
    PositionIterator endP = facade.getObjects().find(end);
    manager.rotateX(begin, end, beginP, endP, ax);
    manager.rotateY(begin, end, beginP, endP, ay);
    manager.rotateZ(begin, end, beginP, endP, az);
}
