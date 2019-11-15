#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QKeyEvent>
#include <QDebug>

#include "Commands/Offset.h"
#include "Commands/Rotate.h"
#include "Commands/Scale.h"
#include "Commands/Load.h"
#include "Commands/Save.h"
#include "Commands/AddParticle.h"
#include "Commands/MoveCamera.h"
#include "Commands/RotateCamera.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);
    void mousePressedEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);

private:
    Ui::MainWindow *ui;

    Scene facade;
    Point2D prev;
};

#endif // __MAINWINDOW_H
