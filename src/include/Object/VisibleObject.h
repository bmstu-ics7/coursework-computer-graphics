#ifndef __VISIBLEOBJECT_H
#define __VISIBLEOBJECT_H

#include "Object.h"

class VisibleObject : public Object
{
public:
    VisibleObject() { visible = true; compose = false; }
};

#endif // __VISIBLEOBJECT_H
