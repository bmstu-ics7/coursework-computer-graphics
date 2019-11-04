#ifndef __GLDRAW_H
#define __GLDRAW_H

#include <QtOpenGL>
#include "Drawer.h"
#include "Window/OpenGLWidget.h"

class GLDraw : public Drawer
{
public:
    GLDraw(OpenGLWidget& canvas);
    void drawLine(const Point3D& a, const Point3D& b) override;

private:
    OpenGLWidget& canvas;
};

#endif // __GLDRAW_H
