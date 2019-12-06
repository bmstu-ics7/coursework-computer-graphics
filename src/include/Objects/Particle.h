#ifndef __PARTICLE_H
#define __PARTICLE_H

#include <QtOpenGL>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

struct Vertex
{
    Vertex();
    Vertex(QVector3D p, QVector2D t, QVector3D n)
        : position(p), texCoord(t), normal(n) { }

    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
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
