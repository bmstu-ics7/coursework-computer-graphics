#ifndef __PARTICLE_H
#define __PARTICLE_H

#include <QtOpenGL>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

struct VertexOnly
{
    VertexOnly();
    VertexOnly(QVector3D p)
        : position(p) { }

    QVector3D position;
};

class Particle
{
public:
    Particle();
    Particle(GLfloat x, GLfloat y, GLfloat z);
    Particle(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b);
    Particle(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat width);

    void draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions);
    void setColor(GLfloat r, GLfloat g, GLfloat b);

private:
    QOpenGLBuffer _arrayBuffer;
    QOpenGLBuffer _indexBuffer;
    QMatrix4x4 _modelViewMatrix;

    GLfloat _r;
    GLfloat _g;
    GLfloat _b;
};

#endif // __PARTICLE_H
