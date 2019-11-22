#include "Window/MainWindow.h"
#include "ui_MainWindow.h"
#include "Math/PerlinNoise.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->setFacade(&facade);
    QRandomGenerator gen;
    siv::PerlinNoise noise;
/*
    for (double theta = 0; theta < 360; theta += 1) {
        for (double phi = 0; phi < 360;   phi += 1) {
            double x, y, z, r;
            x = 1 * sin(theta * M_PI / 180) * cos(phi * M_PI / 180);
            y = 1 * sin(theta * M_PI / 180) * sin(phi * M_PI / 180);
            z = 1 * cos(theta * M_PI / 180);

            r = noise.octaveNoise0_1(x / 10, y / 10, z / 10, 8.0);

            x *= r;
            y *= r;
            z *= r;

            AddParticle(x, y, z, r, r, r).execute(facade);
        }
    }
    */

    noise.reseed(gen.generate64());
    for (double x = -1; x <= 1; x += 0.002) {
        for (double y = -1; y <= 1; y += 0.002) {
            double c = noise.octaveNoise0_1(x, y, 8);
            AddParticle(x, y, 0, c, c ,c).execute(facade);
        }
    }
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
