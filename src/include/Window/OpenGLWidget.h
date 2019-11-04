#ifndef __OPENGLWIDGET_H
#define __OPENGLWIDGET_H

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

    void setFacade(Scene* facade);

    size_t widht();
    size_t height();

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
