#ifndef __WIDGET_H
#define __WIDGET_H

#define GL_SILENCE_DEPRECATION

/* OpenGL libraries */
#ifdef __APPLE__
#   include <OpenGL/glu.h>
#else
#   include <GL/glu.h>
#endif
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
#include <QOpenGLFramebufferObject>

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
    void addCloud(const QVector3D& center, const QVector3D& coefficient, const QVector3D& color);
    void setTextureSkyBox(const QString& path);

    void setCamera();
    void translateCamera(GLfloat x, GLfloat y, GLfloat z);
    void rotateCamera(QQuaternion angle);

    void keyPressEvent(QKeyEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void wheelEvent(QWheelEvent* e);

    void sunRotateX(int value);
    void sunRotateY(int value);
    void sunRotateZ(int value);

private:
    QMatrix4x4 _projectionMatrix;
    QMatrix4x4 _projectionLightMatrix;
    QMatrix4x4 _camera;
    QMatrix4x4 _lightMatrix;
    QMatrix4x4 _shadowLightMatrix;
    QVector2D _prev;

    QOpenGLShaderProgram _program;
    QOpenGLShaderProgram _programSkyBox;
    QOpenGLShaderProgram _programDepth;

    QList< Particle > _particles;
    SkyBox skyBox;

    GLfloat _translateX;
    GLfloat _translateY;
    GLfloat _translateZ;
    QQuaternion _angle;

    GLfloat _lightRotateX;
    GLfloat _lightRotateY;
    GLfloat _lightRotateZ;

    QOpenGLFramebufferObject* _depthBuffer;
    size_t _fbWidth;
    size_t _fbHeight;
};

#endif // __WIDGET_H
