#include "Window/MainWindow.h"
#include "ui_MainWindow.h"
#include "Math/PerlinNoise.hpp"
#include "Math/TileableVolumeNoise.h"

void MainWindow::addCloud(glm::vec3 center, glm::vec3 coefficient)
{
    double x, y, z, r;
    siv::PerlinNoise noise;
    noise.reseed(rand());

    for (double theta = 0; theta < 360; theta += 2) {
        for (double phi = 0; phi < 360;   phi += 2) {
            x = coefficient[0] * sin(theta * M_PI / 180) * cos(phi * M_PI / 180);
            y = coefficient[1] * sin(theta * M_PI / 180) * sin(phi * M_PI / 180);
            z = coefficient[2] * cos(theta * M_PI / 180);

            r = noise.octaveNoise0_1(x / 2, y / 2, z / 2, 8);

            x = center[0] + x * r;
            y = center[1] + y * r;
            z = center[2] + z * r;

            AddParticle(x, y, z, r, r, r).execute(facade);
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->setFacade(&facade);

    srand(time(NULL));

    //addCloud(glm::vec3(-2, -2, 0), glm::vec3(2, 1, 1), Mode::Perlin);
    addCloud(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    switch (e->key()) {
    case Qt::Key_Up:
        RotateCamera(2, 0, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_Down:
        RotateCamera(-2, 0, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_Left:
        RotateCamera(0, -2, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_Right:
        RotateCamera(0, 2, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_J:
        MoveCamera(ActionMove::Forward, 0.95, 0.95, 0.95).execute(facade);
        repaint();
        break;
    case Qt::Key_K:
        MoveCamera(ActionMove::Back, 1.05, 1.05, 1.05).execute(facade);
        repaint();
        break;
    case Qt::Key_W:
        MoveCamera(ActionMove::Up, 0, 0.1, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_A:
        MoveCamera(ActionMove::Left, -0.1, 0, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_S:
        MoveCamera(ActionMove::Down, 0, -0.1, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_D:
        MoveCamera(ActionMove::Right, 0.1, 0, 0).execute(facade);
        repaint();
        break;
    }
}

void MainWindow::paintEvent(QPaintEvent*)
{
    ui->canvas->update();
}


void MainWindow::mousePressedEvent(QMouseEvent* e)
{
    prev = Point2D(e->x(), e->y());
}

void MainWindow::mouseMoveEvent(QMouseEvent* e)
{
    int y = 180 * (e->x() - prev.x()) / width();
    int x = 180 * (e->y() - prev.y()) / height();

    RotateCamera((double)x, (double)y, 0).execute(facade);
    prev = Point2D(e->x(), e->y());

    repaint();
}

void MainWindow::wheelEvent(QWheelEvent* e)
{
    if (e->delta() > 0)
        MoveCamera(ActionMove::Back, 1.05, 1.05, 1.05).execute(facade);
    else if (e->delta() < 0)
        MoveCamera(ActionMove::Forward, 0.95, 0.95, 0.95).execute(facade);

    repaint();
}
