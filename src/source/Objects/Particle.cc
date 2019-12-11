#include "Objects/Particle.h"

QOpenGLBuffer Particle::_arrayBuffer;
QOpenGLBuffer Particle::_indexBuffer;

Particle::Particle() :
    Particle(0.0, 0.0, 0.0) { }

Particle::Particle(GLfloat x, GLfloat y, GLfloat z)
    : Particle(x, y, z, 1.0, 1.0, 1.0) { }

Particle::Particle(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b)
    : Particle(x, y, z, r, g, b, 0.1) { }

Particle::Particle(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat width)
    : _r(r), _g(g), _b(b)
{
    _modelViewMatrix.setToIdentity();
    _modelViewMatrix.translate(x, y, z);
}

void Particle::initialization()
{
    GLfloat w = 0.1f / 2.0f;
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
}

void Particle::firstDraw(QOpenGLShaderProgram* program)
{
    _arrayBuffer.bind();

    int offset = 0;

    int posLoc = program->attributeLocation("a_position");
    program->enableAttributeArray(posLoc);
    program->setAttributeBuffer(posLoc, GL_FLOAT, offset, 3, sizeof(VertexOnly));

    _indexBuffer.bind();
}

void Particle::draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions)
{
    program->setUniformValue("u_modelMatrix", _modelViewMatrix);
    program->setUniformValue("u_color", QVector4D(_r, _g, _b, 1.0f));
    functions->glDrawElements(GL_TRIANGLES, _indexBuffer.size(), GL_UNSIGNED_INT, 0);
}
