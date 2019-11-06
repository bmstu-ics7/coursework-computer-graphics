#ifndef __MODEL_H
#define __MODEL_H

#include "Object/VisibleObject.h"
#include "Object/Edge.h"
#include "Object/Point2D.h"

class Model : public VisibleObject
{
public:
    Model() : VisibleObject() { }

    void addPoint(Point3D point);
    void addEdge(Edge edge);

    void draw(Drawer& drawer) override;
    void scale(const Point3D& center, double k) override;
    void offset(double dx, double dy, double dz) override;
    void rotateX(const Point3D& center, double a) override;
    void rotateY(const Point3D& center, double a) override;
    void rotateZ(const Point3D& center, double a) override;

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
