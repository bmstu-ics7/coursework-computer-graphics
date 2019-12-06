#include "Objects/Particle.h"

Particle::Particle() :
    Particle(0.0, 0.0, 0.0) { }

Particle::Particle(GLfloat x, GLfloat y, GLfloat z)
    : Particle(x, y, z, 1.0, 1.0, 1.0) { }

Particle::Particle(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b)
    : Particle(x, y, z, r, g, b, 0.05) { }

Particle::Particle(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat width)
    : _r(r), _g(g), _b(b)
{
    GLfloat w = width / 2.0f;
    QVector< Vertex > vertex;

    // front
    vertex.append(Vertex(QVector3D(x - w, y + w, z + w), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertex.append(Vertex(QVector3D(x - w, y - w, z + w), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertex.append(Vertex(QVector3D(x + w, y + w, z + w), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertex.append(Vertex(QVector3D(x + w, y - w, z + w), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    // right
    vertex.append(Vertex(QVector3D(x + w, y + w, z + w), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertex.append(Vertex(QVector3D(x + w, y - w, z + w), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertex.append(Vertex(QVector3D(x + w, y + w, z - w), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertex.append(Vertex(QVector3D(x + w, y - w, z - w), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    // top
    vertex.append(Vertex(QVector3D(x + w, y + w, z + w), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertex.append(Vertex(QVector3D(x + w, y + w, z - w), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertex.append(Vertex(QVector3D(x - w, y + w, z + w), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertex.append(Vertex(QVector3D(x - w, y + w, z - w), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

    //back
    vertex.append(Vertex(QVector3D(x + w, y + w, z - w), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertex.append(Vertex(QVector3D(x + w, y - w, z - w), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertex.append(Vertex(QVector3D(x - w, y + w, z - w), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertex.append(Vertex(QVector3D(x - w, y - w, z - w), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    // left
    vertex.append(Vertex(QVector3D(x - w, y + w, z + w), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertex.append(Vertex(QVector3D(x - w, y + w, z - w), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertex.append(Vertex(QVector3D(x - w, y - w, z + w), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertex.append(Vertex(QVector3D(x - w, y - w, z - w), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    // bottom
    vertex.append(Vertex(QVector3D(x - w, y - w, z + w), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertex.append(Vertex(QVector3D(x - w, y - w, z - w), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertex.append(Vertex(QVector3D(x + w, y - w, z + w), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertex.append(Vertex(QVector3D(x + w, y - w, z - w), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));

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
    _arrayBuffer.allocate(vertex.constData(), vertex.size() * sizeof(Vertex));
    _arrayBuffer.release();

    _indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    _indexBuffer.create();
    _indexBuffer.bind();
    _indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    _indexBuffer.release();

    _modelViewMatrix.setToIdentity();
    _modelViewMatrix.translate(0.0, 0.0, -10.0);
    _modelViewMatrix.rotate(30, 1.0, 0.0, 0.0);
    _modelViewMatrix.rotate(30, 0.0, 1.0, 0.0);
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
