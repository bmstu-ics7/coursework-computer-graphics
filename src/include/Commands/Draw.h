#ifndef __DRAW_H
#define __DRAW_H

#include "Command.h"
#include "Drawing/QtDraw.h"

class Draw : Command
{
public:
    Draw(ObjectIterator begin,
         Drawer& drawer)
        : Command(begin), drawer(drawer) { }

    Draw(ObjectIterator begin, ObjectIterator end,
         Drawer& drawer)
        : Command(begin, end), drawer(drawer) { }

    void execute(Scene& facade) override;

private:
    Drawer& drawer;
};

#endif // __DRAW_H
