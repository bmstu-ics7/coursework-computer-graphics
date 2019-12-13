#include "Widget/MainWindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->sunRotateX, &QSlider::valueChanged, this, &MainWindow::sunRotateX);
    QObject::connect(ui->sunRotateY, &QSlider::valueChanged, this, &MainWindow::sunRotateY);
    QObject::connect(ui->sunRotateZ, &QSlider::valueChanged, this, &MainWindow::sunRotateZ);
    QObject::connect(ui->btnCloudColor, &QPushButton::clicked, this, &MainWindow::clickCloudColor);
    QObject::connect(ui->btnAddCloud, &QPushButton::clicked, this, &MainWindow::clickAddCloud);
    QObject::connect(ui->btnLoadSkyBox, &QPushButton::clicked, this, &MainWindow::clickLoadSkyBox);
    QObject::connect(ui->btnUp, &QPushButton::clicked, this, &MainWindow::clickUp);
    QObject::connect(ui->btnDown, &QPushButton::clicked, this, &MainWindow::clickDown);
    QObject::connect(ui->btnLeft, &QPushButton::clicked, this, &MainWindow::clickLeft);
    QObject::connect(ui->btnRight, &QPushButton::clicked, this, &MainWindow::clickRight);

    ui->canvas->sunRotateX(ui->sunRotateX->value());
    ui->canvas->sunRotateY(ui->sunRotateY->value());
    ui->canvas->sunRotateZ(ui->sunRotateZ->value());

    _cloudColor = Qt::white;

    QString qss = QString("background-color: %1;").arg(_cloudColor.name());
    qss += " border-style: solid; border-width: 1px; border-color: gray;";
    ui->btnCloudColor->setStyleSheet(qss);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sunRotateX(int value)
{
    ui->canvas->sunRotateX(value);
    ui->lblSunRotateX->setText(QString::number(value));
}

void MainWindow::sunRotateY(int value)
{
    ui->canvas->sunRotateY(value);
    ui->lblSunRotateY->setText(QString::number(value));
}

void MainWindow::sunRotateZ(int value)
{
    ui->canvas->sunRotateZ(value);
    ui->lblSunRotateZ->setText(QString::number(value));
}

void MainWindow::clickCloudColor()
{
    QColorDialog* color = new QColorDialog();
    color->open();
    _cloudColor = color->getColor();

    QString qss = QString("background-color: %1;").arg(_cloudColor.name());
    qss += " border-style: solid; border-width: 1px; border-color: gray;";
    ui->btnCloudColor->setStyleSheet(qss);

    delete color;
}

void MainWindow::clickAddCloud()
{
    QVector3D center = QVector3D(ui->centerX->value(), ui->centerY->value(), ui->centerZ->value());
    QVector3D param = QVector3D(ui->parameterX->value(), ui->parameterY->value(), ui->parameterZ->value());
    QVector3D color = QVector3D(_cloudColor.red() / 255.0, _cloudColor.green() / 255.0, _cloudColor.blue() / 255.0);
    ui->canvas->addCloud(center, param, color);
}

void MainWindow::clickLoadSkyBox()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    ui->canvas->setTextureSkyBox(fileName);
}

void MainWindow::clickUp()
{
    ui->canvas->translateCamera(0.0f, -1.0f, 0.0f);
}

void MainWindow::clickDown()
{
    ui->canvas->translateCamera(0.0f, 1.0f, 0.0f);
}

void MainWindow::clickLeft()
{
    ui->canvas->translateCamera(-1.0f, 0.0f, 0.0f);
}

void MainWindow::clickRight()
{
    ui->canvas->translateCamera(1.0f, 0.0f, 0.0f);
}
