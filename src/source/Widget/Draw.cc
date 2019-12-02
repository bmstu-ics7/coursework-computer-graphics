#include "Widget/Widget.h"
#include <QDebug>

Widget::Widget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    srand(time(NULL));
    addCloud(glm::vec3(0, 0, 0), glm::vec3(2, 1, 1));
    update();
}

void Widget::initializeGL()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_NORMALIZE);
}

void Widget::resizeGL(int newWidth, int newHeight)
{
    _width = newWidth;
    _height = newHeight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void Widget::paintGL()
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

    setCamera();
    sky();
    drawParticles();

    glPopMatrix();
}

void Widget::drawParticles()
{
    for (Particle particle : particles) {
        drawParticle(particle);
    }
}

void Widget::drawParticle(const Particle& particle)
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
            glColor3f(particle.r(), particle.g(), particle.b());
            for (int j = 0; j < 4; ++j) {
                glVertex3f(verges[i][j][0], verges[i][j][1], verges[i][j][2]);
            }
        glEnd();
    }
}

void Widget::sky()
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
