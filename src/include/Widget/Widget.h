#ifndef __WIDGET_H
#define __WIDGET_H

#define GL_SILENCE_DEPRECATION

/* OpenGL libraries */
#include <OpenGL/glu.h>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include "glm/glm.hpp"

/* QT libraries */
#include <QVector3D>
#include <QList>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPoint>

#include "Objects/Particle.h"
#include "Noise/PerlinNoise.hpp"
#include "Noise/TileableVolumeNoise.h"

class Widget : public QOpenGLWidget
{
    Q_OBJECT

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

public:
    Widget(QWidget* parent = 0);

    void sky();
    void drawParticles();
    void drawParticle(const Particle& particle);

    GLdouble noise(siv::PerlinNoise n, double x, double y, double z);
    void addCloud(glm::vec3 center, glm::vec3 coefficient);

    void setCamera();
    void offsetCamera(GLdouble x, GLdouble y, GLdouble z);
    void scaleCamera(GLdouble k);
    void rotateCamera(GLint x, GLint y, GLint z);

    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    size_t _width;
    size_t _height;

    QPoint prev;

    QList< Particle > particles;

    GLdouble _scaleX = 1;
    GLdouble _scaleY = 1;
    GLdouble _scaleZ = 1;

    GLdouble _offsetX = 0;
    GLdouble _offsetY = 0;
    GLdouble _offsetZ = 0;

    GLint _rotateX = 0;
    GLint _rotateY = 0;
    GLint _rotateZ = 0;
};

#endif // __WIDGET_H
