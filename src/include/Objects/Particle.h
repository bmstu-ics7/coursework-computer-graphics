#ifndef __PARTICLE_H
#define __PARTICLE_H

#include <QtOpenGL>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

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

    QOpenGLBuffer& arrayBuffer();
    QOpenGLBuffer& indexBuffer();
    QMatrix4x4& modelViewMatrix();

    const QOpenGLBuffer& arrayBuffer() const;
    const QOpenGLBuffer& indexBuffer() const;
    const QMatrix4x4& modelViewMatrix() const;

    void setColor(GLfloat r, GLfloat g, GLfloat b);

    GLfloat r();
    GLfloat g();
    GLfloat b();

    GLfloat r() const;
    GLfloat g() const;
    GLfloat b() const;

private:
    QOpenGLBuffer _arrayBuffer;
    QOpenGLBuffer _indexBuffer;
    QMatrix4x4 _modelViewMatrix;

    GLfloat _r;
    GLfloat _g;
    GLfloat _b;
};

#endif // __PARTICLE_H
