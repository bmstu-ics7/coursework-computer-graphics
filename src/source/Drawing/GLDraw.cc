#include "Drawing/GLDraw.h"

GLDraw::GLDraw(OpenGLWidget& canvas)
    : Drawer(canvas.width(), canvas.height()),
    canvas(canvas) { }

void GLDraw::drawLine(const Point3D& a, const Point3D& b)
{
    canvas.drawLine(a, b);
}
