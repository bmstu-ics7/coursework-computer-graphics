#ifndef __WIDGET_H
#define __WIDGET_H

#define GL_SILENCE_DEPRECATION

/* OpenGL libraries */
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
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
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLTexture>

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

    void initShaders();

public:
    Widget(QWidget* parent = nullptr);

    double noise(siv::PerlinNoise n, double x, double y, double z);
    void addCloud(glm::vec3 center, glm::vec3 coefficient);

private:
    QMatrix4x4 _projectionMatrix;
    QOpenGLShaderProgram _program;
    QOpenGLTexture* _texture;

    QList< Particle > _particles;
};

#endif // __WIDGET_H
