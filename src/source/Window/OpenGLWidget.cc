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
    glFrustum(-_width, _width, -_height, _height, 500.0f, 500.0f);
    glViewport(0, 0, (GLint)_width, (GLint)_height);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glMatrixMode(GL_PROJECTION);

    try {
        ObjectIterator begin = facade->getObjects().beginObjects();
        ObjectIterator end = facade->getObjects().endObjects();
        GLDraw drawer(*(this), facade->getMatrix());
        Draw(begin, end, drawer).execute(*facade);
    } catch (std::bad_alloc e) {
        qDebug() << e.what();
    } catch (std::exception e) {
        qDebug() << "paint exception";
        qDebug() << e.what();
    }

    glPopMatrix();
}

void OpenGLWidget::drawLine(const Point3D& a, const Point3D& b)
{
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f((GLfloat)a.x(), (GLfloat)a.y(), (GLfloat)a.z());
        glVertex3f((GLfloat)b.x(), (GLfloat)b.y(), (GLfloat)b.z());
    glEnd();
}

void OpenGLWidget::drawParticle(const Point3D& particle)
{
    glPointSize(3.0f);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);

    glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f((GLfloat)particle.x(), (GLfloat)particle.y(), (GLfloat)particle.z());
    glEnd();
}

void OpenGLWidget::setFacade(Scene* facade)
{
    this->facade = facade;
}

size_t OpenGLWidget::widht() { return _width; }

size_t OpenGLWidget::height() { return _height; }

void OpenGLWidget::setCamera(GLfloat ox, GLfloat oy, GLfloat oz,
                             GLfloat sx, GLfloat sy, GLfloat sz,
                             GLfloat ax, GLfloat ay, GLfloat az)
{
    glTranslatef(ox, oy, oz);
    glScalef(sx, sy, sz);
    glRotatef(ax, 1.0f, 0.0f, 0.0f);
    glRotatef(ay, 0.0f, 1.0f, 0.0f);
    glRotatef(az, 0.0f, 0.0f, 1.0f);
}
