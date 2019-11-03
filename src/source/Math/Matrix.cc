#include "Math/Matrix.h"

Matrix::Matrix() : Matrix(0) { }

Matrix::Matrix(size_t size) : _size(size)
{
    for (size_t i = 0; i < _size; ++i) {
        std::vector< GLfloat > line;

        for (size_t j = 0; j < _size; ++j) {
            line.push_back(0.0f);
        }

        _data.push_back(line);
    }
}

std::vector< GLfloat > Matrix::operator[](int index)
{
    return _data[index];
}


const size_t Matrix::size()
{
    return _size;
}
