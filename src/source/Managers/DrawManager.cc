#include "Managers/DrawManager.h"

void DrawManager::draw(ObjectIterator begin, ObjectIterator end, Drawer &drawer)
{
    ObjectIterator iter = begin;
    for (; iter != end; ++iter) {
        std::shared_ptr< Object > obj = *iter;
        obj->draw(drawer);
    }
}
