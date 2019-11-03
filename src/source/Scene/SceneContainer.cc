#include "Scene/SceneContainer.h"

SceneContainer::SceneContainer() { }

size_t SceneContainer::size()
{
    return objects.size();
}

void SceneContainer::add(std::shared_ptr< Object > obj)
{
    objects.push_back(obj);
}

void SceneContainer::addPosition(std::shared_ptr< Position > pos)
{
    positions.push_back(pos);
}

PositionIterator SceneContainer::find(ObjectIterator iter)
{
    ObjectIterator io = beginObjects();
    PositionIterator ip = beginPositions();
    for (; io != iter; ++io, ++ip);
    return ip;
}

ObjectIterator SceneContainer::beginObjects()
{
    return objects.begin();
}

ObjectIterator SceneContainer::endObjects()
{
    return objects.end();
}

PositionIterator SceneContainer::beginPositions()
{
    return positions.begin();
}

PositionIterator SceneContainer::endPositions()
{
    return positions.end();
}
