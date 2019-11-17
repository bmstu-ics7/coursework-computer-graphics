#ifndef __GLDRAW_H
#define __GLDRAW_H

#include <QtOpenGL>
#include "Drawer.h"
#include "Window/OpenGLWidget.h"

class GLDraw : public Drawer
{
public:
    GLDraw(OpenGLWidget& canvas, Camera camera);
    void drawLine(const Point3D& a, const Point3D& b) override;
    void drawParticle(const Point3D& particle) override;
    void setCamera() override;

private:
    OpenGLWidget& canvas;
};

#endif // __GLDRAW_H
