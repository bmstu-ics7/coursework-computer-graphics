#ifndef __WIDGET_H
#define __WIDGET_H

#include <OpenGL/glu.h>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QVector3D>
#include <QQuaternion>
#include <QList>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPoint>

#include "glm/glm.hpp"
#include "Particle.h"
#include "Noise/PerlinNoise.hpp"
#include "Noise/TileableVolumeNoise.h"

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = 0);

    void drawParticle(const Particle& particle);

    void sky();
    void setCamera();
    void drawParticles();
    void addCloud(glm::vec3 center, glm::vec3 coefficient);
    void keyPressEvent(QKeyEvent* e);

    void offsetCamera(GLdouble x, GLdouble y, GLdouble z);
    void scaleCamera(GLdouble k);
    void rotateCamera(GLint x, GLint y, GLint z);

    void mousePressedEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void wheelEvent(QWheelEvent* e);

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

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
