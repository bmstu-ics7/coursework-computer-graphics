#ifndef __OPENGLWIDGET_H
#define __OPENGLWIDGET_H

#ifndef __APPLE__
#include <OpenGL/glu.h>
#elif __linux__
#include <GL/glu.h>
#endif

#include <QtOpenGL>
#include <QOpenGLWidget>
#include "Object/Point3D.h"
#include "Scene/Scene.h"

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget* parent = 0);

    void drawLine(const Point3D& a, const Point3D& b);
    void drawParticle(const Point3D& particle, double r, double g, double b);

    void setFacade(Scene* facade);

    size_t widht();
    size_t height();

    void setCamera(GLfloat ox, GLfloat oy, GLfloat oz,
                   GLfloat sx, GLfloat sy, GLfloat sz,
                   GLfloat ax, GLfloat ay, GLfloat az);

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

private:
    Scene* facade;

    size_t _width;
    size_t _height;
};

#endif // __OPENGLWIDGET_H
