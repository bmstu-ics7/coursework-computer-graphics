#ifndef __DRAWMANAGER_H
#define __DRAWMANAGER_H

#include "Manager.h"

class DrawManager : public Manager
{
public:
    DrawManager() { }

    void draw(ObjectIterator begin, ObjectIterator end, Drawer& drawer);
};

#endif // __DRAWMANAGER_H
