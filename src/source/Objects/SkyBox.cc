#include "Objects/SkyBox.h"

SkyBox::SkyBox() :
    SkyBox(0.0, 0.0, 0.0, 0.0) { }

SkyBox::SkyBox(GLfloat x, GLfloat y, GLfloat z, GLfloat width)
    : _texture(nullptr)
{
    GLfloat w = width / 2.0f;
    QVector< VertexTex > vertex;

    // front
    vertex.append(VertexTex(QVector3D(-w, +w, -w), QVector2D(0.25, 2.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(-w, -w, -w), QVector2D(0.25, 1.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(+w, +w, -w), QVector2D(0.50, 2.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(+w, -w, -w), QVector2D(0.50, 1.0 / 3.0)));

    // left
    vertex.append(VertexTex(QVector3D(-w, +w, +w), QVector2D(0.00, 2.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(-w, -w, +w), QVector2D(0.00, 1.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(-w, +w, -w), QVector2D(0.25, 2.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(-w, -w, -w), QVector2D(0.25, 1.0 / 3.0)));

    // bottom
    vertex.append(VertexTex(QVector3D(+w, -w, +w), QVector2D(0.50, 0.00)));
    vertex.append(VertexTex(QVector3D(+w, -w, -w), QVector2D(0.50, 1.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(-w, -w, +w), QVector2D(0.25, 0.00)));
    vertex.append(VertexTex(QVector3D(-w, -w, -w), QVector2D(0.25, 1.0 / 3.0)));

    //back
    vertex.append(VertexTex(QVector3D(+w, +w, +w), QVector2D(0.75, 2.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(+w, -w, +w), QVector2D(0.75, 1.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(-w, +w, +w), QVector2D(1.00, 2.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(-w, -w, +w), QVector2D(1.00, 1.0 / 3.0)));

    // right
    vertex.append(VertexTex(QVector3D(+w, +w, +w), QVector2D(0.75, 2.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(+w, +w, -w), QVector2D(0.50, 2.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(+w, -w, +w), QVector2D(0.75, 1.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(+w, -w, -w), QVector2D(0.50, 1.0 / 3.0)));

    // top
    vertex.append(VertexTex(QVector3D(-w, +w, +w), QVector2D(0.25, 1.00)));
    vertex.append(VertexTex(QVector3D(-w, +w, -w), QVector2D(0.25, 2.0 / 3.0)));
    vertex.append(VertexTex(QVector3D(+w, +w, +w), QVector2D(0.50, 1.00)));
    vertex.append(VertexTex(QVector3D(+w, +w, -w), QVector2D(0.50, 2.0 / 3.0)));

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

void SkyBox::setTexture(QString path)
{
    _texture = new QOpenGLTexture(QImage(path).mirrored());
    _texture->setMagnificationFilter(QOpenGLTexture::Nearest);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    _texture->setWrapMode(QOpenGLTexture::Repeat);
}

void SkyBox::draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions)
{
    _texture->bind(0);
    program->setUniformValue("u_modelMatrix", _modelViewMatrix);
    program->setUniformValue("u_texture", 0);

    _arrayBuffer.bind();

    int offset = 0;

    int posLoc = program->attributeLocation("a_position");
    program->enableAttributeArray(posLoc);
    program->setAttributeBuffer(posLoc, GL_FLOAT, offset, 3, sizeof(VertexTex));

    offset += sizeof(QVector3D);

    int texLoc = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texLoc);
    program->setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof(VertexTex));

    _indexBuffer.bind();

    functions->glDrawElements(GL_TRIANGLES, _indexBuffer.size(), GL_UNSIGNED_INT, 0);
}
