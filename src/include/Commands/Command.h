#ifndef __COMMAND_H
#define __COMMAND_H

#include "Scene/Scene.h"
#include "Scene/Iterator.h"

class Command
{
public:
    virtual void execute(Scene& facade) = 0;
    virtual ~Command() = default;

protected:
    Command() { }
    Command(ObjectIterator begin) : begin(begin) { end = begin + 1; }
    Command(ObjectIterator begin, ObjectIterator end) : begin(begin), end(end) { }

    ObjectIterator begin;
    ObjectIterator end;
};

#endif // __COMMAND_H
