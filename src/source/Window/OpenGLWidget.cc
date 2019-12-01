#include "Window/OpenGLWidget.h"
#include "Commands/Draw.h"
#include <QDebug>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent) { }

void OpenGLWidget::initializeGL()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_NORMALIZE);
}

void OpenGLWidget::resizeGL(int newWidth, int newHeight)
{
    _width = newWidth;
    _height = newHeight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    glViewport(0, 0, (GLint)_width * 2, (GLint)_height * 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-(GLfloat)_width / 600, (GLfloat)_width / 600,
            -(GLfloat)_height / 600, (GLfloat)_height / 600,
            -2, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_SMOOTH);

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

void OpenGLWidget::drawParticle(const Point3D& particle, double r, double g, double b)
{
    glMatrixMode(GL_MODELVIEW);
    const double d = 0.05;

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int i = 0; i < 6; ++i) {
        glBegin(GL_QUADS);
            glColor3f(r, g, b);
            for (int j = 0; j < 4; ++j) {
                glVertex3f(verges[i][j][0], verges[i][j][1], verges[i][j][2]);
            }
        glEnd();
    }
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

void OpenGLWidget::skyBox()
{
    glPushMatrix();
    glTranslatef(0.0f, -50.0f, 0.0f);

    GLdouble eq[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
    glClipPlane(GL_CLIP_PLANE0, eq);
    glEnable(GL_CLIP_PLANE0);

    glColor3f(0.49, 0.78, 1.0);
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere(quadric, 100, 18, 18);
    glDisable(GL_CLIP_PLANE0);

    glBegin(GL_QUADS);
        glColor3f(0.41f, 0.19f, 0.01f);
        glVertex3f(+100, 0, -100);
        glVertex3f(+100, 0, +100);
        glVertex3f(-100, 0, +100);
        glVertex3f(-100, 0, -100);
    glEnd();

    glPopMatrix();
}
