#include "Window/OpenGLWidget.h"
#include "Commands/Draw.h"
#include <QDebug>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

void OpenGLWidget::initializeGL()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void OpenGLWidget::resizeGL(int newWidth, int newHeight)
{
    _width = newWidth;
    _height = newHeight;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat overw = (GLfloat)_width / _height;
    GLfloat overh = (GLfloat)_height / _width;
    glFrustum(-100.0 * overw, +100.0 * overw,
              -1.0   * overh, +1.0   * overh,
              +1.0, +1.0
             );
    glViewport(0, 0, (GLint)_width, (GLint)_height);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    try {
        ObjectIterator begin = facade->getObjects().beginObjects();
        ObjectIterator end = facade->getObjects().endObjects();
        GLDraw drawer(*(this));
        Draw(begin, end, drawer).execute(*facade);
    } catch (std::bad_alloc e) {
        qDebug() << e.what();
    } catch (std::exception e) {
        qDebug() << "paint exception";
        qDebug() << e.what();
    }
}

void OpenGLWidget::drawLine(const Point3D& a, const Point3D& b)
{
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f((GLfloat)a.getX(), (GLfloat)a.getY(), (GLfloat)a.getZ());
    glVertex3f((GLfloat)b.getX(), (GLfloat)b.getY(), (GLfloat)b.getZ());
    glEnd();
}

void OpenGLWidget::setFacade(Scene* facade)
{
    this->facade = facade;
}

size_t OpenGLWidget::widht() { return _width; }

size_t OpenGLWidget::height() { return _height; }

//void OpenGLWidget::draw
