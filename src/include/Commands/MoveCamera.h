#ifndef __MOVECAMERA_H
#define __MOVECAMERA_H

#include "Command.h"
#include "Object/Camera.h"
#include "ActionMove.h"

class MoveCamera : Command
{
public:
    MoveCamera(ActionMove action, GLfloat x, GLfloat y, GLfloat z, GLfloat distance = 1)
        : action(action), x(x), y(y), z(z), distance(distance) { }
    void execute(Scene& facade) override;

private:
    ActionMove action;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat distance;
};

#endif // __MOVECAMERA_H
