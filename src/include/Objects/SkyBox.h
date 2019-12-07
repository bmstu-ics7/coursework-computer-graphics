#ifndef __SKYBOX_H
#define __SKYBOX_H

#include <QtOpenGL>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

struct VertexTex
{
    VertexTex();
    VertexTex(QVector3D p, QVector2D t)
        : position(p), textureCoord(t) { }

    QVector3D position;
    QVector2D textureCoord;
};

class SkyBox
{
public:
    SkyBox();
    SkyBox(GLfloat x, GLfloat y, GLfloat z, GLfloat width);

    QOpenGLBuffer& arrayBuffer();
    QOpenGLBuffer& indexBuffer();
    QMatrix4x4& modelViewMatrix();

    const QOpenGLBuffer& arrayBuffer() const;
    const QOpenGLBuffer& indexBuffer() const;
    const QMatrix4x4& modelViewMatrix() const;

private:
    QOpenGLBuffer _arrayBuffer;
    QOpenGLBuffer _indexBuffer;
    QMatrix4x4 _modelViewMatrix;
};

#endif // __SKYBOX_H
