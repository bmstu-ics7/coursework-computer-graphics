#ifndef __BUILDER_H
#define __BUILDER_H

#include <stdlib.h>

#include "Object/Model.h"

class Builder
{
public:
    Builder() { }
};

class ModelBuilder : public Builder
{
public:
    ModelBuilder()  { model.reset(); }

    void createModel();
    void buildPoint(const double x, const double y, const double z);
    void buildEdge(const size_t start, const size_t finish);
    std::shared_ptr< Model > get();

private:
    std::shared_ptr< Model > model;
};

#endif // __BUILDER_H
