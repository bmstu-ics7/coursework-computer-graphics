#ifndef __MODEL_H
#define __MODEL_H

#include "Object/VisibleObject.h"
#include "Drawing/Drawer.h"
#include "Object/Edge.h"
#include "Object/Point2D.h"

class Model : public VisibleObject
{
public:
    Model() : VisibleObject() { }

    void addPoint(Point3D point);
    void addEdge(Edge edge);

    std::vector< Point3D >& getPoints();
    std::vector< Edge >& getEdges();

    const std::vector< Point3D >& getPoints() const;
    const std::vector< Edge >& getEdges() const;

    std::vector< Point3D > getConstPoints();
    std::vector< Edge > getConstEdges();

private:
    std::vector< Edge > edges;
    std::vector< Point3D > points;
};

#endif // __MODEL_H
