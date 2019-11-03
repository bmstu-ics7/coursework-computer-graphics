#ifndef __OFFSET_H
#define __OFFSET_H

#include "Command.h"

class Offset : Command
{
public:
    Offset(ObjectIterator begin,
           const double dx, const double dy, const double dz)
        : Command(begin), dx(dx), dy(dy), dz(dz) { }

    Offset(ObjectIterator begin, ObjectIterator end,
           const double dx, const double dy, const double dz)
        : Command(begin, end), dx(dx), dy(dy), dz(dz) { }

    void execute(Scene& facade) override;

private:
    const double dx;
    const double dy;
    const double dz;
};

#endif // __OFFSET_H
