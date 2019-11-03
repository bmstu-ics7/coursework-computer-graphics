#ifndef __SCALE_H
#define __SCALE_H

#include "Command.h"

class Scale : Command
{
public:
    Scale(ObjectIterator begin,
          const double k)
        : Command(begin), k(k) { }

    Scale(ObjectIterator begin, ObjectIterator end,
          const double k)
        : Command(begin, end), k(k) { }

    void execute(Scene& facade) override;

private:
    const double k;
};

#endif // __SCALE_H
