#include "Widget.h"
#include <QDebug>

double noise(siv::PerlinNoise n, double x, double y, double z)
{
    double n1 = Tileable3dNoise::WorleyNoise(glm::vec3(x, y, z), 4);
    double n2 = Tileable3dNoise::WorleyNoise(glm::vec3(x, y, z), 8);
    double r = 0.1 + ((1 - n1) * 1.5 -  n2 * 0.7) * 0.8 + n.octaveNoise0_1(x * 5, y * 5, z * 5, 8);
    return r;
}

void Widget::addCloud(glm::vec3 center, glm::vec3 coefficient)
{
    double x, y, z, r;
    siv::PerlinNoise noisePerlin;
    noisePerlin.reseed(rand());

    for (double theta = 0; theta < 360; theta += 2) {
        for (double phi = 0; phi < 360;   phi += 2) {
            x = coefficient[0] * sin(theta * M_PI / 180) * cos(phi * M_PI / 180);
            y = coefficient[1] * sin(theta * M_PI / 180) * sin(phi * M_PI / 180);
            z = coefficient[2] * cos(theta * M_PI / 180);

            r = noisePerlin.octaveNoise0_1(x / 2, y / 2, z / 2, 8) +
                noise(noisePerlin, x / 2, y / 2, z / 2) * 0.2;

            x = center[0] + x * r;
            y = center[1] + y * r;
            z = center[2] + z * r;

            particles.append(Particle(x, y, z, r, r, r));
        }
    }
}

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

void Widget::setCamera()
{
    glTranslatef(_offsetX, _offsetY, _offsetZ);
    glScalef(_scaleX, _scaleY, _scaleZ);
    glRotatef(_rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(_rotateY, 0.0f, 1.0f, 0.0f);
    glRotatef(_rotateZ, 0.0f, 0.0f, 1.0f);
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

void Widget::keyPressEvent(QKeyEvent* e)
{
    switch (e->key()) {
    case Qt::Key_Up:
        rotateCamera(2, 0, 0);
        update();
        break;
    case Qt::Key_Down:
        rotateCamera(2, 0, 0);
        update();
        break;
    case Qt::Key_Left:
        rotateCamera(0, -2, 0);
        update();
        break;
    case Qt::Key_Right:
        rotateCamera(0, 2, 0);
        update();
        break;
    case Qt::Key_J:
        scaleCamera(0.95);
        update();
        break;
    case Qt::Key_K:
        scaleCamera(1.05);
        update();
        break;
    case Qt::Key_W:
        offsetCamera(0, 0.1, 0);
        update();
        break;
    case Qt::Key_A:
        offsetCamera(-0.1, 0, 0);
        update();
        break;
    case Qt::Key_S:
        offsetCamera(0, -0.1, 0);
        update();
        break;
    case Qt::Key_D:
        offsetCamera(0.1, 0, 0);
        update();
        break;
    }
}

void Widget::offsetCamera(GLdouble x, GLdouble y, GLdouble z)
{
    _offsetX += x;
    _offsetY += y;
    _offsetZ += z;
}

void Widget::scaleCamera(GLdouble k)
{
    _scaleX *= k;
    _scaleY *= k;
    _scaleZ *= k;
}

void Widget::rotateCamera(GLint x, GLint y, GLint z)
{
    _rotateX += x;
    _rotateX %= 360;

    _rotateY += y;
    _rotateY %= 360;

    _rotateZ += z;
    _rotateZ %= 360;
}

void Widget::mousePressedEvent(QMouseEvent* e)
{
    if (e->buttons() == Qt::LeftButton)
        prev = QPoint(e->localPos().x(), e->localPos().y());
    e->accept();
}

void Widget::mouseMoveEvent(QMouseEvent* e)
{
    if (e->buttons() != Qt::LeftButton) return;

    GLint y = 180 * (e->localPos().x() - prev.x()) / width();
    GLint x = 180 * (e->localPos().y() - prev.y()) / height();

    rotateCamera(x, y, 0);
    prev = QPoint(e->localPos().x(), e->localPos().y());

    update();
}

void Widget::wheelEvent(QWheelEvent* e)
{
    if (e->delta() > 0)
        scaleCamera(1.05);
    else if (e->delta() < 0)
        scaleCamera(0.95);

    repaint();
}
