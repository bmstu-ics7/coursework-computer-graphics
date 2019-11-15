#ifndef __MATRIX_H
#define __MATRIX_H

#include <QtOpenGL>
#include <stdlib.h>
#include <vector>
#include <cmath>

class Matrix
{
public:
    Matrix();
    Matrix(size_t size);

    std::vector< GLfloat >& operator[](int index);
    const size_t size();

private:
    std::vector< std::vector< GLfloat > > _data;
    size_t _size;
};

#endif // __MATRIX_H
