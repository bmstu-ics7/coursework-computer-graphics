#include "Commands/Scale.h"

void Scale::execute(Scene& facade)
{
    TransformManager manager = facade.getTransformManager();
    PositionIterator beginP = facade.getObjects().find(begin);
    PositionIterator endP = facade.getObjects().find(end);
    manager.scale(begin, end, beginP, endP, k);
}
