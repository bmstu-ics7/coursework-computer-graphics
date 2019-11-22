#include "Window/OpenGLWidget.h"
#include "Commands/Draw.h"
#include <QDebug>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent) { }

void OpenGLWidget::initializeGL()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    // glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
}

void OpenGLWidget::resizeGL(int newWidth, int newHeight)
{
    _width = newWidth;
    _height = newHeight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)_width, (GLint)_height);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    // glShadeModel(GL_SMOOTH);

    /*
    GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

    GLfloat light0_diffuse[] = {1.0, 1.0, 1.0};
    GLfloat light0_direction[] = {1.0, 1.0, 1.0, 0.0};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
    */

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
    // glDisable(GL_LIGHT0);
}

void OpenGLWidget::drawLine(const Point3D& a, const Point3D& b)
{
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f((GLfloat)a.x(), (GLfloat)a.y(), (GLfloat)a.z());
        glVertex3f((GLfloat)b.x(), (GLfloat)b.y(), (GLfloat)b.z());
    glEnd();
}

void OpenGLWidget::drawParticle(const Point3D& particle, double r, double g, double b)
{
    glMatrixMode(GL_MODELVIEW);
    const double d = 0.01;

    double verges[6][4][3] =
    {
        {
            // Лицевая грань
            { particle.x() - d, particle.y() + d, particle.z() + d },
            { particle.x() + d, particle.y() + d, particle.z() + d },
            { particle.x() + d, particle.y() - d, particle.z() + d },
            { particle.x() - d, particle.y() - d, particle.z() + d }
        },

        {
            // Задняя грань
            { particle.x() - d, particle.y() + d, particle.z() - d },
            { particle.x() + d, particle.y() + d, particle.z() - d },
            { particle.x() + d, particle.y() - d, particle.z() - d },
            { particle.x() - d, particle.y() - d, particle.z() - d }
        },

        {
            // Левая грань
            { particle.x() - d, particle.y() + d, particle.z() + d },
            { particle.x() - d, particle.y() + d, particle.z() - d },
            { particle.x() - d, particle.y() - d, particle.z() - d },
            { particle.x() - d, particle.y() - d, particle.z() + d }
        },

        {
            // Правая грань
            { particle.x() + d, particle.y() + d, particle.z() + d },
            { particle.x() + d, particle.y() + d, particle.z() - d },
            { particle.x() + d, particle.y() - d, particle.z() - d },
            { particle.x() + d, particle.y() - d, particle.z() + d }
        },

        {
            // Верхняя грань
            { particle.x() - d, particle.y() + d, particle.z() + d },
            { particle.x() - d, particle.y() + d, particle.z() - d },
            { particle.x() + d, particle.y() + d, particle.z() - d },
            { particle.x() + d, particle.y() + d, particle.z() + d }
        },

        {
            // Нижняя грань
            { particle.x() - d, particle.y() - d, particle.z() + d },
            { particle.x() - d, particle.y() - d, particle.z() - d },
            { particle.x() + d, particle.y() - d, particle.z() - d },
            { particle.x() + d, particle.y() - d, particle.z() + d }
        }
    };

    for (int i = 0; i < 6; ++i) {
        glBegin(GL_QUADS);
            glColor3f(r, g, b);
            for (int j = 0; j < 4; ++j) {
                glVertex3f(verges[i][j][0], verges[i][j][1], verges[i][j][2]);
            }
        glEnd();
    }

    /*
    glPointSize(1.0f);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);

    glBegin(GL_POINTS);
        glColor3f(r, g, b);
        glVertex3f((GLfloat)particle.x(), (GLfloat)particle.y(), (GLfloat)particle.z());
    glEnd();
    */
    /*
    glPushMatrix();
    glTranslatef(particle.x(), particle.y(), particle.z());
    gluSphere(gluNewQuadric(), 0.02, 10, 10);
    glPopMatrix();
    */
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
    glRotatef(ax, 1.0f, 0.0f, 0.0f) ;
    glRotatef(ay, 0.0f, 1.0f, 0.0f);
    glRotatef(az, 0.0f, 0.0f, 1.0f);
}
