#include "Window/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    /*
    QPainter painter(this);
    int canvasHeight = height();
    int canvasWidth = width() - 220;
    painter.setClipRect(0, 0, canvasWidth, canvasHeight);
    painter.fillRect(0, 0, canvasWidth, canvasHeight, "#222");

    try {
        ObjectIterator begin = facade.getObjects().beginObjects();
        ObjectIterator end = facade.getObjects().endObjects();
        QtDraw drawer(painter, size_t(canvasWidth), size_t(canvasHeight));
        Draw(begin, end, drawer).execute(facade);
    } catch (std::bad_alloc e) {
        qDebug() << e.what();
    } catch (std::exception e) {
        qDebug() << "paint exception";
        qDebug() << e.what();
    }
    */
    ui->canvas->paintGL();
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
