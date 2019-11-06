#include "Window/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->setFacade(&facade);
    AddParticle(0, 0, 0).execute(facade);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    ui->canvas->update();
}

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
