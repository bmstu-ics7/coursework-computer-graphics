#include "Object/Model.h"
#include <QDebug>

void Model::addPoint(Point3D point)
{
    points.push_back(point);
}

void Model::addEdge(Edge edge)
{
    edges.push_back(edge);
}

void Model::draw(Drawer& drawer)
{
    for (size_t i = 0; i < edges.size(); ++i) {
        drawer.drawLine(points[edges[i].getStart()],
                        points[edges[i].getFinish()]);
    }
}

void Model::scale(const Point3D& center, double k)
{
    for (auto& point : points) point.scale(center, k);
}

void Model::offset(double dx, double dy, double dz)
{
    for (auto& point : points) point.offset(dx, dy, dz);
}

void Model::rotateX(const Point3D& center, double a)
{
    for (auto& point : points) point.rotateX(center, a);
}

void Model::rotateY(const Point3D& center, double a)
{
    for (auto& point : points) point.rotateY(center, a);
}

void Model::rotateZ(const Point3D& center, double a)
{
    for (auto& point : points) point.rotateZ(center, a);
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
