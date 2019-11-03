#ifndef __SCENECONTAINER_H
#define __SCENECONTAINER_H

#include <stdlib.h>
#include <vector>

#include "Object/Model.h"
#include "Object/Position.h"
#include "Object/Camera.h"
#include "Iterator.h"

class SceneContainer
{
public:
    SceneContainer();

    size_t size();

    void add(std::shared_ptr< Object > obj);
    void addPosition(std::shared_ptr< Position > pos);

    PositionIterator find(ObjectIterator iter);

    ObjectIterator beginObjects();
    ObjectIterator endObjects();
    PositionIterator beginPositions();
    PositionIterator endPositions();

private:
    std::vector< std::shared_ptr< Object > > objects;
    std::vector< std::shared_ptr< Position > > positions;
};

#endif // __SCENECONTAINER_H
