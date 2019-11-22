#ifndef __ROTATE_H
#define __ROTATE_H

#include "Command.h"

class Rotate : Command
{
public:
    Rotate(ObjectIterator begin,
           const double ax, const double ay, const double az)
        : Command(begin), ax(ax), ay(ay), az(az) { }

    Rotate(ObjectIterator begin, ObjectIterator end,
           const double ax, const double ay, const double az)
        : Command(begin, end), ax(ax), ay(ay), az(az) { }

    void execute(Scene& facade) override;

private:
    const double ax;
    const double ay;
    const double az;
};

#endif // __ROTATE_H
