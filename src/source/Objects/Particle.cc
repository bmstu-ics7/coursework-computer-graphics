#include "Objects/Particle.h"

Particle::Particle() :
    Particle(0.0, 0.0, 0.0) { }

Particle::Particle(GLfloat x, GLfloat y, GLfloat z)
    : Particle(x, y, z, 1.0, 1.0, 1.0) { }

Particle::Particle(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b)
    : Particle(x, y, z, r, g, b, 0.1) { }

Particle::Particle(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat width)
    : _r(r), _g(g), _b(b)
{
    GLfloat w = width / 2.0f;
    QVector< VertexOnly > vertex;

    // front
    vertex.append(VertexOnly(QVector3D(-w, +w, +w)));
    vertex.append(VertexOnly(QVector3D(-w, -w, +w)));
    vertex.append(VertexOnly(QVector3D(+w, +w, +w)));
    vertex.append(VertexOnly(QVector3D(+w, -w, +w)));

    // right
    vertex.append(VertexOnly(QVector3D(+w, +w, +w)));
    vertex.append(VertexOnly(QVector3D(+w, -w, +w)));
    vertex.append(VertexOnly(QVector3D(+w, +w, -w)));
    vertex.append(VertexOnly(QVector3D(+w, -w, -w)));

    // top
    vertex.append(VertexOnly(QVector3D(+w, +w, +w)));
    vertex.append(VertexOnly(QVector3D(+w, +w, -w)));
    vertex.append(VertexOnly(QVector3D(-w, +w, +w)));
    vertex.append(VertexOnly(QVector3D(-w, +w, -w)));

    //back
    vertex.append(VertexOnly(QVector3D(+w, +w, -w)));
    vertex.append(VertexOnly(QVector3D(+w, -w, -w)));
    vertex.append(VertexOnly(QVector3D(-w, +w, -w)));
    vertex.append(VertexOnly(QVector3D(-w, -w, -w)));

    // left
    vertex.append(VertexOnly(QVector3D(-w, +w, +w)));
    vertex.append(VertexOnly(QVector3D(-w, +w, -w)));
    vertex.append(VertexOnly(QVector3D(-w, -w, +w)));
    vertex.append(VertexOnly(QVector3D(-w, -w, -w)));

    // bottom
    vertex.append(VertexOnly(QVector3D(-w, -w, +w)));
    vertex.append(VertexOnly(QVector3D(-w, -w, -w)));
    vertex.append(VertexOnly(QVector3D(+w, -w, +w)));
    vertex.append(VertexOnly(QVector3D(+w, -w, -w)));

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
    _arrayBuffer.allocate(vertex.constData(), vertex.size() * sizeof(VertexOnly));
    _arrayBuffer.release();

    _indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    _indexBuffer.create();
    _indexBuffer.bind();
    _indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    _indexBuffer.release();

    _modelViewMatrix.setToIdentity();
    _modelViewMatrix.translate(x, y, z);
}

void Particle::setColor(GLfloat r, GLfloat g, GLfloat b)
{
    _r = r;
    _g = g;
    _b = b;
}

QOpenGLBuffer& Particle::arrayBuffer() { return _arrayBuffer; }
QOpenGLBuffer& Particle::indexBuffer() { return _indexBuffer; }
QMatrix4x4& Particle::modelViewMatrix() { return _modelViewMatrix; }

const QOpenGLBuffer& Particle::arrayBuffer() const { return _arrayBuffer; }
const QOpenGLBuffer& Particle::indexBuffer() const { return _indexBuffer; }
const QMatrix4x4& Particle::modelViewMatrix() const { return _modelViewMatrix; }

GLfloat Particle::r() { return _r; }
GLfloat Particle::g() { return _g; }
GLfloat Particle::b() { return _b; }

GLfloat Particle::r() const { return _r; }
GLfloat Particle::g() const { return _g; }
GLfloat Particle::b() const { return _b; }
