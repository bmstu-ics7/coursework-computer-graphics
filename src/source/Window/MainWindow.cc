#include "Window/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->setFacade(&facade);
    for (double x = -1; x <= 1; x += 0.05)
        for (double y = -1; y <= 1; y += 0.05)
            for (double z = -1; z <= 1; z += 0.05)
                AddParticle(x, y, z).execute(facade);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    switch (e->key()) {
    case Qt::Key_Up:
        RotateCamera(1, 0, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_Down:
        RotateCamera(-1, 0, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_Left:
        RotateCamera(0, -1, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_Right:
        RotateCamera(0, 1, 0).execute(facade);
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

    qDebug() << x << y;

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
