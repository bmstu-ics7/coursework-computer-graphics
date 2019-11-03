#include "Window/OpenGLWidget.h"

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

void OpenGLWidget::initializeGL()
{
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
}

void OpenGLWidget::resizeGL(int newWidth, int newHeight)
{
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
