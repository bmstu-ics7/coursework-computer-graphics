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
#include <QQuaternion>
#include <QVector2D>

#include "Objects/Particle.h"
#include "Objects/SkyBox.h"
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
    void addCloud(QVector3D center, QVector3D coefficient);

    void setCamera();
    void translateCamera(GLfloat x, GLfloat y, GLfloat z);
    void scaleCamera(GLfloat k);
    void rotateCamera(QQuaternion angle);

    void keyPressEvent(QKeyEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void wheelEvent(QWheelEvent* e);

private:
    QMatrix4x4 _projectionMatrix;
    QMatrix4x4 _camera;
    QVector2D _prev;

    QOpenGLShaderProgram _program;
    QOpenGLShaderProgram _programSkyBox;
    QOpenGLTexture* _textureSkyBox;

    QList< Particle > _particles;
    SkyBox skyBox;

    GLfloat _scale;
    GLfloat _translateX;
    GLfloat _translateY;
    GLfloat _translateZ;
    QQuaternion _angle;
};

#endif // __WIDGET_H
