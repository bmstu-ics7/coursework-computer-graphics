#ifndef __OBJECT_H
#define __OBJECT_H

class Object
{
public:
    Object() { }
    bool isVisible() { return visible; }
    bool isCompose() { return compose; }

protected:
    bool visible;
    bool compose;
};

#endif // __OBJECT_H
