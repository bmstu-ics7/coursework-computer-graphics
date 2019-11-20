#include "Drawing/GLDraw.h"

GLDraw::GLDraw(OpenGLWidget& canvas, Camera camera)
    : Drawer(canvas.width(), canvas.height(), camera),
    canvas(canvas) { }

void GLDraw::drawLine(const Point3D& a, const Point3D& b)
{
    canvas.drawLine(a, b);
}

void GLDraw::drawParticle(const Point3D& particle)
{
    canvas.drawParticle(particle);
}

void GLDraw::setCamera()
{
    canvas.setCamera(camera.offsetX(), camera.offsetY(), camera.offsetZ(),
                     camera.scaleX(), camera.scaleY(), camera.scaleZ(),
                     camera.rotateX(), camera.rotateY(), camera.rotateZ());
}
