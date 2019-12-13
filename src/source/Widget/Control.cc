#include "Widget/Widget.h"
#include <QDebug>

double Widget::noise(siv::PerlinNoise n, double x, double y, double z)
{
    double n1 = Tileable3dNoise::WorleyNoise(glm::vec3(x, y, z), 4);
    double n2 = Tileable3dNoise::WorleyNoise(glm::vec3(x, y, z), 8);
    double r = 0.1 + ((1 - n1) * 1.5 -  n2 * 0.7) * 0.8 + n.octaveNoise0_1(x * 5, y * 5, z * 5, 20);
    return r;
}

void Widget::addCloud(const QVector3D& center, const QVector3D& coefficient, const QVector3D& color)
{
    double x, y, z, r;
    siv::PerlinNoise noisePerlin;
    noisePerlin.reseed(rand());

    for (double theta = 0; theta < 360; theta += 2) {
        for (double phi = 0; phi < 360;   phi += 2) {
            x = coefficient[0] * sin(theta * M_PI / 180) * cos(phi * M_PI / 180);
            y = coefficient[1] * sin(theta * M_PI / 180) * sin(phi * M_PI / 180);
            z = coefficient[2] * cos(theta * M_PI / 180);

            r = noisePerlin.octaveNoise0_1(x / 2, y / 2, z / 2, 20) +
                noise(noisePerlin, x / 2, y / 2, z / 2) * 0.3;

            x = center[0] + x * r;
            y = center[1] + y * r;
            z = center[2] + z * r;

            _particles.append(Particle(x, y, z, color.x(), color.y(), color.z()));
        }
    }

    update();
}

Widget::Widget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    srand(uint(time(nullptr)));
    _translateX = 0;
    _translateY = 0;
    _translateZ = -10;

    _fbHeight = 1024;
    _fbWidth = 1024;
}

void Widget::keyPressEvent(QKeyEvent* e)
{
    switch (e->key()) {
    case Qt::Key_W:
        translateCamera(0, 0, 0.5);
        update();
        break;
    case Qt::Key_A:
        translateCamera(0.5, 0, 0);
        update();
        break;
    case Qt::Key_S:
        translateCamera(0, 0, -0.5);
        update();
        break;
    case Qt::Key_D:
        translateCamera(-0.5, 0, 0);
        update();
        break;
    }
}

void Widget::mousePressEvent(QMouseEvent* e)
{
    if (e->buttons() == Qt::LeftButton)
        _prev = QVector2D(e->localPos());
    e->accept();
}

void Widget::mouseMoveEvent(QMouseEvent* e)
{
    if (e->buttons() != Qt::LeftButton) return;

    QVector2D diff = QVector2D(e->localPos()) - _prev;
    _prev = QVector2D(e->localPos());

    float angle = diff.length() / 2.0f;
    QVector2D axis(diff.y(), diff.x());
    rotateCamera(QQuaternion::fromAxisAndAngle(axis, angle));

    update();
}

void Widget::wheelEvent(QWheelEvent* e)
{
    if (e->delta() > 0)
        translateCamera(0, 0, -0.5);
    else if (e->delta() < 0)
        translateCamera(0, 0, 0.5);

    update();
}

void Widget::sunRotateX(int value)
{
    _lightRotateX = value;
    update();
}

void Widget::sunRotateY(int value)
{
    _lightRotateY = value;
    update();
}

void Widget::sunRotateZ(int value)
{
    _lightRotateZ = value;
    update();
}

void Widget::setTextureSkyBox(const QString& path)
{
    skyBox.setTexture(path);
    update();
}
