#include "Widget/Widget.h"
#include <QOpenGLContext>
#include <QDebug>

void Widget::initializeGL()
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    _depthBuffer = new QOpenGLFramebufferObject(_fbWidth, _fbHeight, QOpenGLFramebufferObject::Depth);

    skyBox = SkyBox(0, 0, 0, 500);
    skyBox.setTexture("../textures/skybox_texture.jpg");

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

    _program.bind();
    _program.setUniformValue("u_projectionMatrix", _projectionMatrix);
    _program.setUniformValue("u_viewMatrix", _camera);

    for (Particle& particle : _particles) {
        particle.draw(&_program, context()->functions());
    }

    _programSkyBox.bind();
    _programSkyBox.setUniformValue("u_projectionMatrix", _projectionMatrix);
    _programSkyBox.setUniformValue("u_viewMatrix", _camera);
    skyBox.draw(&_programSkyBox, context()->functions());
}
