#include "Object/Builder.h"

void ModelBuilder::createModel()
{
    model.reset(new Model());
}

void ModelBuilder::buildPoint(const double x, const double y, const double z)
{
    model.get()->addPoint(Point3D(x, y, z));
}

void ModelBuilder::buildEdge(const size_t start, const size_t finish)
{
    model.get()->addEdge(Edge(start, finish));
}

std::shared_ptr< Model > ModelBuilder::get()
{
    return model;
}
