#include "Drawing/GLDraw.h"

GLDraw::GLDraw(OpenGLWidget& canvas, Camera camera)
    : Drawer(canvas.width(), canvas.height(), camera),
    canvas(canvas) { }

void GLDraw::drawLine(const Point3D& a, const Point3D& b)
{
    canvas.drawLine(camera.multiplication(a), camera.multiplication(b));
}

void GLDraw::drawParticle(const Point3D& particle)
{
    canvas.drawParticle(camera.multiplication(particle));
}
