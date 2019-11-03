#include "Object/Model.h"

void Model::addPoint(Point3D point)
{
    points.push_back(point);
}

void Model::addEdge(Edge edge)
{
    edges.push_back(edge);
}

std::vector< Point3D >& Model::getPoints()
{
    return points;
}

std::vector< Edge >& Model::getEdges()
{
    return edges;
}

const std::vector< Point3D >& Model::getPoints() const
{
    return points;
}

const std::vector< Edge >& Model::getEdges() const
{
    return edges;
}

std::vector< Point3D > Model::getConstPoints()
{
    return points;
}

std::vector< Edge > Model::getConstEdges()
{
    return edges;
}
