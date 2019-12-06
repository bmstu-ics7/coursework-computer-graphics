#include "Widget/Widget.h"
#include <QDebug>

void Widget::initializeGL()
{
    _texture = new QOpenGLTexture(QImage("../textures/cube.jpg").mirrored());
    _texture->setMagnificationFilter(QOpenGLTexture::Nearest);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    _texture->setWrapMode(QOpenGLTexture::Repeat);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    _particles.append(Particle(0, 0, 0, 1, 1, 1, 1));
    _particles.append(Particle(2, 0, 0, 1, 1, 1, 1));
    _particles.append(Particle(-2, 0, 0, 1, 1, 1, 1));
    initShaders();
}

void Widget::initShaders()
{
    if (!_program.addShaderFromSourceFile(QOpenGLShader::Vertex, "../shaders/vshader.vsh"))
        close();

    if (!_program.addShaderFromSourceFile(QOpenGLShader::Fragment, "../shaders/fshader.fsh"))
        close();

    if (!_program.link())
        close();
}

void Widget::resizeGL(int width, int height)
{
    float aspect = width / float(height);

    _projectionMatrix.setToIdentity();
    _projectionMatrix.perspective(45, aspect, 0.1f, 100.0f);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _texture->bind(0);

    for (Particle& particle : _particles) {
        _program.bind();
        _program.setUniformValue("qt_ModelViewProjectionMatrix", _projectionMatrix * particle.modelViewMatrix());
        _program.setUniformValue("qt_Texture0", 0);

        particle.arrayBuffer().bind();

        int offset = 0;

        int vertLoc = _program.attributeLocation("qt_Vertex");
        _program.enableAttributeArray(vertLoc);
        _program.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(Vertex));

        offset += sizeof(QVector3D);

        int texLoc = _program.attributeLocation("qt_MultiTexCoord0");
        _program.enableAttributeArray(texLoc);
        _program.setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof(Vertex));

        particle.indexBuffer().bind();

        glDrawElements(GL_TRIANGLES, particle.indexBuffer().size(), GL_UNSIGNED_INT, 0);
    }
}
