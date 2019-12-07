#include "Widget/Widget.h"
#include <QDebug>

void Widget::initializeGL()
{
    _textureSkyBox = new QOpenGLTexture(QImage("../textures/skybox_texture.jpg").mirrored());
    _textureSkyBox->setMagnificationFilter(QOpenGLTexture::Nearest);
    _textureSkyBox->setMagnificationFilter(QOpenGLTexture::Linear);
    _textureSkyBox->setWrapMode(QOpenGLTexture::Repeat);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    skyBox = SkyBox(0, 0, 0, 500);
    addCloud(QVector3D(0, 0, 0), QVector3D(2, 1, 1));
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

    if (!_programSkyBox.addShaderFromSourceFile(QOpenGLShader::Vertex, "../shaders/vSkyBox.vsh"))
        close();

    if (!_programSkyBox.addShaderFromSourceFile(QOpenGLShader::Fragment, "../shaders/fSkyBox.fsh"))
        close();

    if (!_programSkyBox.link())
        close();
}

void Widget::resizeGL(int width, int height)
{
    float aspect = width / float(height);

    _projectionMatrix.setToIdentity();
    _projectionMatrix.perspective(45, aspect, 0.1f, 700.0f);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setCamera();

    for (Particle& particle : _particles) {
        _program.bind();
        _program.setUniformValue("u_projectionMatrix", _projectionMatrix);
        _program.setUniformValue("u_viewMatrix", _camera);
        _program.setUniformValue("u_modelMatrix", particle.modelViewMatrix());
        _program.setUniformValue("u_color", QVector4D(particle.r(), particle.g(), particle.b(), 1.0f));

        particle.arrayBuffer().bind();

        int offset = 0;

        int posLoc = _program.attributeLocation("a_position");
        _program.enableAttributeArray(posLoc);
        _program.setAttributeBuffer(posLoc, GL_FLOAT, offset, 3, sizeof(VertexOnly));

        particle.indexBuffer().bind();

        glDrawElements(GL_TRIANGLES, particle.indexBuffer().size(), GL_UNSIGNED_INT, 0);
    }

    _textureSkyBox->bind(0);

    _programSkyBox.bind();
    _programSkyBox.setUniformValue("u_projectionMatrix", _projectionMatrix);
    _programSkyBox.setUniformValue("u_viewMatrix", _camera);
    _programSkyBox.setUniformValue("u_modelMatrix", skyBox.modelViewMatrix());
    _programSkyBox.setUniformValue("u_texture", 0);

    skyBox.arrayBuffer().bind();

    int offset = 0;

    int posLoc = _programSkyBox.attributeLocation("a_position");
    _programSkyBox.enableAttributeArray(posLoc);
    _programSkyBox.setAttributeBuffer(posLoc, GL_FLOAT, offset, 3, sizeof(VertexTex));

    offset += sizeof(QVector3D);

    int texLoc = _programSkyBox.attributeLocation("a_texcoord");
    _programSkyBox.enableAttributeArray(texLoc);
    _programSkyBox.setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof(VertexTex));

    skyBox.indexBuffer().bind();

    glDrawElements(GL_TRIANGLES, skyBox.indexBuffer().size(), GL_UNSIGNED_INT, 0);
}
