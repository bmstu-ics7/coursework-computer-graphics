#include "Commands/Draw.h"

void Draw::execute(Scene& facade)
{
    DrawManager manager = facade.getDrawManager();
    manager.draw(begin, end, drawer);
}
