#include "Managers/DrawManager.h"

void DrawManager::draw(ObjectIterator begin, ObjectIterator end, Drawer &drawer)
{
    drawer.setCamera();
    drawer.skyBox();
    ObjectIterator iter = begin;
    for (; iter != end; ++iter) {
        std::shared_ptr< Object > obj = *iter;
        if (obj->isVisible())
            obj->draw(drawer);
    }
}
