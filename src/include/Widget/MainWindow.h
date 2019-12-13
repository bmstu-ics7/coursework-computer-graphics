#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QFileDialog>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void sunRotateX(int value);
    void sunRotateY(int value);
    void sunRotateZ(int value);

    void clickCloudColor();
    void clickAddCloud();
    void clickLoadSkyBox();

    void clickUp();
    void clickDown();
    void clickLeft();
    void clickRight();

private:
    Ui::MainWindow* ui;

    QColor _cloudColor;
};

#endif // __MAINWINDOW_H
