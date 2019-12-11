#include "Widget/Widget.h"
#include <QOpenGLContext>
#include <QDebug>

void Widget::initializeGL()
{
    _projectionLightMatrix.setToIdentity();
    _projectionLightMatrix.ortho(-40, 40, -40, 40, -40, 40);

    _lightRotateX = 40;
    _lightRotateY = 40;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    _depthBuffer = new QOpenGLFramebufferObject(_fbWidth, _fbHeight, QOpenGLFramebufferObject::Depth);

    skyBox = SkyBox(0, 0, 0, 500);
    skyBox.setTexture("../textures/skybox_texture.png");

    Particle::initialization();

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

    if (!_programDepth.addShaderFromSourceFile(QOpenGLShader::Vertex, "../shaders/depth.vsh"))
        close();

    if (!_programDepth.addShaderFromSourceFile(QOpenGLShader::Fragment, "../shaders/depth.fsh"))
        close();

    if (!_programDepth.link())
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
    _depthBuffer->bind();

    glViewport(0, 0, _fbWidth, _fbHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _programDepth.bind();
    _programDepth.setUniformValue("u_projectionLightMatrix", _projectionLightMatrix);
    _programDepth.setUniformValue("u_shadowLightMatrix", _shadowLightMatrix);
    Particle::firstDraw(&_programDepth);

    for (Particle& particle : _particles) {
        particle.draw(&_programDepth, context()->functions());
    }

    _programDepth.release();

    _depthBuffer->release();

    GLuint texture = _depthBuffer->texture();

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, texture);

    glViewport(0, 0, width() * 2, height() * 2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setCamera();

    _program.bind();
    _program.setUniformValue("u_projectionMatrix", _projectionMatrix);
    _program.setUniformValue("u_viewMatrix", _camera);
    _program.setUniformValue("u_lightDirection", QVector4D(0.0, 0.0, -1.0, 0.0));
    _program.setUniformValue("u_projectionLightMatrix", _projectionLightMatrix);
    _program.setUniformValue("u_shadowLightMatrix", _shadowLightMatrix);
    _program.setUniformValue("u_lightMatrix", _lightMatrix);
    _program.setUniformValue("u_shadowMap", GL_TEXTURE4 - GL_TEXTURE0);
    Particle::firstDraw(&_program);

    for (Particle& particle : _particles) {
        particle.draw(&_program, context()->functions());
    }

    _program.release();

    _programSkyBox.bind();
    _programSkyBox.setUniformValue("u_projectionMatrix", _projectionMatrix);
    _programSkyBox.setUniformValue("u_viewMatrix", _camera);
    skyBox.draw(&_programSkyBox, context()->functions());
    _programSkyBox.release();
}
