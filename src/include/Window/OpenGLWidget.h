#ifndef __OPENGLWIDGET_H
#define __OPENGLWIDGET_H

#include <QtOpenGL>
#include <QOpenGLWidget>

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget* parent = 0);
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();
};

#endif // __OPENGLWIDGET_H
