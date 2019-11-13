#include "Window/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->setFacade(&facade);

    for (double a = -100; a <= 100; a += 0.002) {
        AddParticle(
                1 * cos(2 * a) * sin(a),
                1 * cos(2 * a) * cos(a),
                0).execute(facade);
    }
    AddParticle(1, -1, 0).execute(facade);
    AddParticle(-1, 1, 0).execute(facade);
    AddParticle(-1, -1, 0).execute(facade);
    AddParticle(1, 1, 0).execute(facade);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    switch (e->key()) {
    case Qt::Key_J:
        MoveCamera(ActionMove::Forward, 0.95, 0.95, 1).execute(facade);
        repaint();
        break;
    case Qt::Key_K:
        MoveCamera(ActionMove::Back, 1.05, 1.05, 1).execute(facade);
        repaint();
        break;
    case Qt::Key_W:
        MoveCamera(ActionMove::Up, 0, 0.05, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_A:
        MoveCamera(ActionMove::Left, -0.05, 0, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_S:
        MoveCamera(ActionMove::Down, 0, -0.05, 0).execute(facade);
        repaint();
        break;
    case Qt::Key_D:
        MoveCamera(ActionMove::Right, 0.05, 0, 0).execute(facade);
        repaint();
        break;
    }
}

void MainWindow::paintEvent(QPaintEvent*)
{
    ui->canvas->update();
}
/*
void MainWindow::on_btnOffset_clicked()
{
    double dx = ui->spinOffsetX->value();
    double dy = ui->spinOffsetY->value();
    double dz = ui->spinOffsetZ->value();

    try {
        ObjectIterator begin = facade.getObjects().beginObjects();
        ObjectIterator end = facade.getObjects().endObjects();
        Offset(begin, end, dx, dy, dz).execute(facade);
    } catch (std::exception e) {
        qDebug() << "offset exception";
        qDebug() << e.what();
    }

    repaint();
}

void MainWindow::on_btnRotate_clicked()
{
    double ax = ui->spinRotateX->value();
    double ay = ui->spinRotateY->value();
    double az = ui->spinRotateZ->value();

    try {
        ObjectIterator begin = facade.getObjects().beginObjects();
        ObjectIterator end = facade.getObjects().endObjects();
        Rotate(begin, end, ax, ay, az).execute(facade);
    } catch (std::exception e) {
        qDebug() << "rotate exception";
        qDebug() << e.what();
    }

    repaint();
}

void MainWindow::on_btnScale_clicked()
{
    double k = ui->spinScale->value();

    try {
        ObjectIterator begin = facade.getObjects().beginObjects();
        ObjectIterator end = facade.getObjects().endObjects();
        Scale(begin, end, k).execute(facade);
    } catch (std::exception e) {
        qDebug() << "scale exception";
        qDebug() << e.what();
    }

    repaint();
}

void MainWindow::on_bntFile_clicked()
{
    try {
        QString fileName = QFileDialog::getOpenFileName(this);
        File file(fileName.toStdString().c_str());
        ModelBuilder build;
        Load(file, build).execute(facade);
    } catch (std::exception e) {
        qDebug() << "load exception";
        qDebug() << e.what();
    }

    repaint();
}

void MainWindow::on_btnSave_clicked()
{
    try {
        QString fileName = QFileDialog::getSaveFileName(this);
        File file(fileName.toStdString().c_str());
        ObjectIterator begin = facade.getObjects().beginObjects();
        ObjectIterator end = facade.getObjects().endObjects();
        Save(begin, end, file);
    } catch (std::exception e) {
        qDebug() << "save exception";
        qDebug() << e.what();
    }

    repaint();
}
*/
