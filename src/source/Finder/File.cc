#include "Finder/File.h"

void File::openLoad()
{
    in.open(fileName);

    if (!in.is_open())
        throw FileException("File not open");
}

void File::openSave()
{
    out.open(fileName);

    if (!out.is_open())
        throw FileException("File not open");
}

void File::close()
{
    if (in.is_open())
        in.close();

    if (out.is_open())
        out.close();
}

std::shared_ptr< Model > File::loadModel(ModelBuilder& builder)
{
    openLoad();
    builder.createModel();

    size_t countPoints = 0;
    in >> countPoints;

    for (size_t i = 0; i < countPoints; ++i) {
        double x, y, z;
        in >> x >> y >> z;
        builder.buildPoint(x, y, z);
    }

    size_t countEdges = 0;
    in >> countEdges;

    for (size_t i = 0; i < countEdges; ++i) {
        size_t a, b;
        in >> a >> b;
        builder.buildEdge(a, b);
    }

    close();

    return builder.get();
}

void File::saveModel(const Model& model)
{
    openSave();

    std::vector< Point3D > points = model.getPoints();
    std::vector< Edge > edges = model.getEdges();

    out << points.size();
    for (Point3D point : points) {
        out << point.x() << ' '
            << point.y() << ' '
            << point.z() << std::endl;
    }

    out << edges.size();
    for (Edge edge : edges) {
        out << edge.getStart() << ' '
            << edge.getFinish() << std::endl;
    }

    close();
}
