#include "Object/Camera.h"
#include <QDebug>

Camera::Camera() : Camera(0.0f, 0.0f, 0.0f) { }

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ)
{
    mat = Matrix(4);
    reverse = Matrix(4);

    mat[0][0] = 1.0f;
    mat[1][1] = 1.0f;
    mat[2][2] = 1.0f;
    mat[3][3] = 1.0f;

    setPosition(posX, posY, posZ);
}


void Camera::setPosition(GLfloat posX, GLfloat posY, GLfloat posZ)
{
    mat[0][3] = posX;
    mat[1][3] = posY;
    mat[2][3] = posZ;

    findReverse();
}

void Camera::move(GLfloat x, GLfloat y, GLfloat z, GLfloat distance)
{
    offsetX += x * distance;
    offsetY += y * distance;
    offsetZ += z * distance;

    /*mat[0][3] += x * distance;
    mat[1][3] += y * distance;
    mat[2][3] += z * distance;

    findReverse();*/
}

void Camera::scale(GLfloat x, GLfloat y, GLfloat z)
{
    scaleX *= x;
    scaleY *= y;
    scaleZ *= z;

    /*mat[0][0] *= x;
    mat[1][1] *= y;
    mat[2][2] *= z;

    findReverse();*/
}

void Camera::rotate(GLfloat x, GLfloat y, GLfloat z)
{
    rotateX += x;
    rotateY += y;
    rotateZ += z;

   /*Matrix mx = matrixRotateX(x);
    Matrix my = matrixRotateY(y);
    Matrix mz = matrixRotateZ(z);

    multiplicationMatrix(mx);
    multiplicationMatrix(my);
    multiplicationMatrix(mz);

    findReverse();*/
}

void Camera::multiplicationMatrix(Matrix& matrix)
{
    Matrix res = Matrix(4);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                res[i][j] = res[i][j] + mat[i][k] * matrix[k][j];
            }
        }
    }

    mat = res;
}

Matrix Camera::matrixRotateX(GLfloat a)
{
    /*
     * Вокруг оси x
     * 1 0    0    0
     * 0 cos  -sin 0
     * 0 sin cos   0
     * 0 0    0    1
     */

    Matrix matrix = Matrix(4);
    matrix[0][0] = 1;
    matrix[1][1] = cos(M_PI * a / 180);
    matrix[1][2] = -sin(M_PI * a / 180);
    matrix[2][1] = sin(M_PI * a / 180);
    matrix[2][2] = cos(M_PI * a / 180);
    matrix[3][3] = 1;
    return matrix;
}

Matrix Camera::matrixRotateY(GLfloat a)
{
    /*
     * Вокруг оси y
     * cos  0 sin 0
     * 0    1 0   0
     * -sin 0 cos 0
     * 0    0 0   1
     */

    Matrix matrix = Matrix(4);
    matrix[0][0] = cos(M_PI * a / 180);
    matrix[0][2] = -sin(M_PI * a / 180);
    matrix[1][1] = 1;
    matrix[2][0] = sin(M_PI * a / 180);
    matrix[2][2] = cos(M_PI * a / 180);
    matrix[3][3] = 1;
    return matrix;
}

Matrix Camera::matrixRotateZ(GLfloat a)
{
    /*
     * Вокруг оси z
     * cos -sin 0 0
     * sin  cos 0 0
     * 0    0   1 0
     * 0    0   0 1
     */

    Matrix matrix = Matrix(4);
    matrix[0][0] = cos(M_PI * a / 180);
    matrix[0][1] = sin(M_PI * a / 180);
    matrix[1][0] = -sin(M_PI * a / 180);
    matrix[1][1] = cos(M_PI * a / 180);
    matrix[2][2] = 1;
    matrix[3][3] = 1;
    return matrix;
}

Point3D Camera::multiplication(const Point3D& point)
{
    double x, y, z;
    x = point.x() * reverse[0][0] + point.y() * reverse[0][1] + point.z() * reverse[0][2] + reverse[0][3];
    y = point.x() * reverse[1][0] + point.y() * reverse[1][1] + point.z() * reverse[1][2] + reverse[1][3];
    z = point.x() * reverse[2][0] + point.y() * reverse[2][1] + point.z() * reverse[2][2] + reverse[2][3];
    return Point3D(x, y, z);
}

void Camera::findReverse()
{
    Matrix matrix = mat;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            reverse[i][j] = i == j ? 1 : 0;

    for (int row = 0; row < 4; row++)
    {
        if (fabs(matrix[row][row]) < 1e-8)
        {
            int change = 0;

            for (int i = row + 1; i < 4; i++)
            {
                if (fabs(matrix[i][row]) > 1e-8)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        double temp;

                        temp = matrix[row][j];
                        matrix[row][j] = matrix[i][j];
                        matrix[i][j] = temp;

                        temp = reverse[row][j];
                        reverse[row][j] = reverse[i][j];
                        reverse[i][j] = temp;
                    }

                    change = 1;
                    break;
                }
            }
        }

        double v = matrix[row][row];

        for (int j = 0; j < 4; j++)
        {
            matrix[row][j] /= v;
            reverse[row][j] /= v;
        }

        for (int i = row + 1; i < 4; i++)
        {
            double v = matrix[i][row];

            for (int j = 0; j < 4; j++)
            {
                matrix[i][j] -= v * matrix[row][j];
                reverse[i][j] -= v * reverse[row][j];
            }
        }
    }

    for (int row = 4 - 1; row > 0; row--)
    {
        for (int i = row - 1; i >= 0; i--)
        {
            double v = matrix[i][row];

            for (int j = 0; j < 4; j++)
            {
                matrix[i][j] -= v * matrix[row][j];
                reverse[i][j] -= v * reverse[row][j];
            }
        }
    }

    qDebug() << "Camera";
    qDebug() << mat[0];
    qDebug() << mat[1];
    qDebug() << mat[2];
    qDebug() << mat[3];
    qDebug() << "";

    qDebug() << "reverse";
    qDebug() << reverse[0];
    qDebug() << reverse[1];
    qDebug() << reverse[2];
    qDebug() << reverse[3];
    qDebug() << "";
}
