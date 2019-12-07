#include "Objects/SkyBox.h"

SkyBox::SkyBox() :
    SkyBox(0.0, 0.0, 0.0, 0.0) { }

SkyBox::SkyBox(GLfloat x, GLfloat y, GLfloat z, GLfloat width)
{
    GLfloat w = width / 2.0f;
    QVector< VertexTex > vertex;

    // front
    vertex.append(VertexTex(QVector3D(-w, +w, -w), QVector2D(0.25, 0.625)));
    vertex.append(VertexTex(QVector3D(-w, -w, -w), QVector2D(0.25, 0.375)));
    vertex.append(VertexTex(QVector3D(+w, +w, -w), QVector2D(0.50, 0.625)));
    vertex.append(VertexTex(QVector3D(+w, -w, -w), QVector2D(0.50, 0.375)));

    // left
    vertex.append(VertexTex(QVector3D(-w, +w, +w), QVector2D(0.00, 0.625)));
    vertex.append(VertexTex(QVector3D(-w, -w, +w), QVector2D(0.00, 0.375)));
    vertex.append(VertexTex(QVector3D(-w, +w, -w), QVector2D(0.25, 0.625)));
    vertex.append(VertexTex(QVector3D(-w, -w, -w), QVector2D(0.25, 0.375)));

    // bottom
    vertex.append(VertexTex(QVector3D(+w, -w, +w), QVector2D(0.25, 0.375)));
    vertex.append(VertexTex(QVector3D(+w, -w, -w), QVector2D(0.25, 0.00)));
    vertex.append(VertexTex(QVector3D(-w, -w, +w), QVector2D(0.50, 0.375)));
    vertex.append(VertexTex(QVector3D(-w, -w, -w), QVector2D(0.50, 0.00)));

    //back
    vertex.append(VertexTex(QVector3D(+w, +w, +w), QVector2D(0.75, 0.625)));
    vertex.append(VertexTex(QVector3D(+w, -w, +w), QVector2D(0.75, 0.375)));
    vertex.append(VertexTex(QVector3D(-w, +w, +w), QVector2D(1.00, 0.625)));
    vertex.append(VertexTex(QVector3D(-w, -w, +w), QVector2D(1.00, 0.375)));

    // right
    vertex.append(VertexTex(QVector3D(+w, +w, +w), QVector2D(0.75, 0.625)));
    vertex.append(VertexTex(QVector3D(+w, +w, -w), QVector2D(0.50, 0.625)));
    vertex.append(VertexTex(QVector3D(+w, -w, +w), QVector2D(0.75, 0.375)));
    vertex.append(VertexTex(QVector3D(+w, -w, -w), QVector2D(0.50, 0.375)));

    // top
    vertex.append(VertexTex(QVector3D(-w, +w, +w), QVector2D(0.25, 1.00)));
    vertex.append(VertexTex(QVector3D(-w, +w, -w), QVector2D(0.25, 0.625)));
    vertex.append(VertexTex(QVector3D(+w, +w, +w), QVector2D(0.50, 1.00)));
    vertex.append(VertexTex(QVector3D(+w, +w, -w), QVector2D(0.50, 0.625)));

    QVector< GLuint > indexes;

    for (int i = 0; i < 24; i += 4) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

    _arrayBuffer.create();
    _arrayBuffer.bind();
    _arrayBuffer.allocate(vertex.constData(), vertex.size() * sizeof(VertexTex));
    _arrayBuffer.release();

    _indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    _indexBuffer.create();
    _indexBuffer.bind();
    _indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    _indexBuffer.release();

    _modelViewMatrix.setToIdentity();
    _modelViewMatrix.translate(x, y, z);
}

QOpenGLBuffer& SkyBox::arrayBuffer() { return _arrayBuffer; }
QOpenGLBuffer& SkyBox::indexBuffer() { return _indexBuffer; }
QMatrix4x4& SkyBox::modelViewMatrix() { return _modelViewMatrix; }

const QOpenGLBuffer& SkyBox::arrayBuffer() const { return _arrayBuffer; }
const QOpenGLBuffer& SkyBox::indexBuffer() const { return _indexBuffer; }
const QMatrix4x4& SkyBox::modelViewMatrix() const { return _modelViewMatrix; }
