#include "Managers/TransformManager.h"

void TransformManager::scale(ObjectIterator beginO, ObjectIterator endO,
                             PositionIterator beginP, PositionIterator endP,
                             const double k)
{
    ObjectIterator iterO = beginO;
    PositionIterator iterP = beginP;

    for (; iterO != endO || iterP != endP; ++iterO, ++iterP) {
        Model* model = (Model*)iterO->get();
        Position* pos = iterP->get();
        Point3D center = pos->get();

        std::vector< Point3D >& points = model->getPoints();
        for (size_t i = 0; i < points.size(); ++i) {
            points[i].scale(center, k);
        }
    }
}

void TransformManager::offset(ObjectIterator beginO, ObjectIterator endO,
                              PositionIterator beginP, PositionIterator endP,
                              const double dx, const double dy, const double dz)
{
    ObjectIterator iterO = beginO;
    PositionIterator iterP = beginP;

    for (; iterO != endO || iterP != endP; ++iterO, ++iterP) {
        Model* model = (Model*)iterO->get();
        Position* pos = iterP->get();
        pos->offset(dx, dy, dz);

        std::vector< Point3D >& points = model->getPoints();
        for (size_t i = 0; i < points.size(); ++i) {
            points[i].offset(dx, dy, dz);
        }
    }
}

void TransformManager::rotateX(ObjectIterator beginO, ObjectIterator endO,
                               PositionIterator beginP, PositionIterator endP,
                               const double angle)
{
    ObjectIterator iterO = beginO;
    PositionIterator iterP = beginP;

    for (; iterO != endO || iterP != endP; ++iterO, ++iterP) {
        Model* model = (Model*)iterO->get();
        Position* pos = iterP->get();
        Point3D center = pos->get();

        std::vector< Point3D >& points = model->getPoints();
        for (size_t i = 0; i < points.size(); ++i) {
            points[i].rotateX(center, angle);
        }
    }
}

void TransformManager::rotateY(ObjectIterator beginO, ObjectIterator endO,
                               PositionIterator beginP, PositionIterator endP,
                               const double angle)
{
    ObjectIterator iterO = beginO;
    PositionIterator iterP = beginP;

    for (; iterO != endO || iterP != endP; ++iterO, ++iterP) {
        Model* model = (Model*)iterO->get();
        Position* pos = iterP->get();
        Point3D center = pos->get();

        std::vector< Point3D >& points = model->getPoints();
        for (size_t i = 0; i < points.size(); ++i) {
            points[i].rotateY(center, angle);
        }
    }
}

void TransformManager::rotateZ(ObjectIterator beginO, ObjectIterator endO,
                               PositionIterator beginP, PositionIterator endP,
                               const double angle)
{
    ObjectIterator iterO = beginO;
    PositionIterator iterP = beginP;

    for (; iterO != endO || iterP != endP; ++iterO, ++iterP) {
        Model* model = (Model*)iterO->get();
        Position* pos = iterP->get();
        Point3D center = pos->get();

        std::vector< Point3D >& points = model->getPoints();
        for (size_t i = 0; i < points.size(); ++i) {
            points[i].rotateZ(center, angle);
        }
    }
}
