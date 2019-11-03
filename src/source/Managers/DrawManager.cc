#include "Managers/DrawManager.h"

void DrawManager::draw(ObjectIterator begin, ObjectIterator end, Drawer &drawer)
{
    ObjectIterator iter = begin;
    for (; iter != end; ++iter) {
        std::shared_ptr< Object > obj = *iter;
        Model model = *(Model*) obj.get();

        std::vector< Point3D > points = model.getConstPoints();
        std::vector< Edge > edges = model.getConstEdges();

        for (size_t i = 0; i < edges.size(); ++i) {
            drawer.drawLine(points[edges[i].getStart()],
                            points[edges[i].getFinish()]);
        }
    }
}
