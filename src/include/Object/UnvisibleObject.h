#ifndef __UNVISIBLEOBJECT_H
#define __UNVISIBLEOBJECT_H

#include "Object.h"

class UnvisibleObject : public Object
{
public:
    UnvisibleObject() { visible = false; compose = false; }
};

#endif // __UNVISIBLEOBJECT_H
