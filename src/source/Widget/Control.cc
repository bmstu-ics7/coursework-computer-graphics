#include "Widget/Widget.h"
#include <QDebug>

double Widget::noise(siv::PerlinNoise n, double x, double y, double z)
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

void Widget::keyPressEvent(QKeyEvent* e)
{
    switch (e->key()) {
    case Qt::Key_Up:
        rotateCamera(-2, 0, 0);
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
