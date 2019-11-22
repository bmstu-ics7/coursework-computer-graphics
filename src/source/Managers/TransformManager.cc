#include "Managers/TransformManager.h"

void TransformManager::scale(ObjectIterator beginO, ObjectIterator endO,
                             PositionIterator beginP, PositionIterator endP,
                             const double k)
{
    ObjectIterator iterO = beginO;
    PositionIterator iterP = beginP;

    for (; iterO != endO || iterP != endP; ++iterO, ++iterP) {
        Object* obj = iterO->get();
        Position* pos = iterP->get();
        Point3D center = pos->get();
        obj->scale(center, k);
    }
}

void TransformManager::offset(ObjectIterator beginO, ObjectIterator endO,
                              PositionIterator beginP, PositionIterator endP,
                              const double dx, const double dy, const double dz)
{
    ObjectIterator iterO = beginO;
    PositionIterator iterP = beginP;

    for (; iterO != endO || iterP != endP; ++iterO, ++iterP) {
        Object* obj = iterO->get();
        obj->offset(dx, dy, dz);

        Position* pos = iterP->get();
        pos->offset(dx, dy, dz);
    }
}

void TransformManager::rotateX(ObjectIterator beginO, ObjectIterator endO,
                               PositionIterator beginP, PositionIterator endP,
                               const double angle)
{
    ObjectIterator iterO = beginO;
    PositionIterator iterP = beginP;

    for (; iterO != endO || iterP != endP; ++iterO, ++iterP) {
        Object* obj = iterO->get();
        Position* pos = iterP->get();
        Point3D center = pos->get();
        obj->rotateX(center, angle);
    }
}

void TransformManager::rotateY(ObjectIterator beginO, ObjectIterator endO,
                               PositionIterator beginP, PositionIterator endP,
                               const double angle)
{
    ObjectIterator iterO = beginO;
    PositionIterator iterP = beginP;

    for (; iterO != endO || iterP != endP; ++iterO, ++iterP) {
        Object* obj = iterO->get();
        Position* pos = iterP->get();
        Point3D center = pos->get();
        obj->rotateY(center, angle);
    }
}

void TransformManager::rotateZ(ObjectIterator beginO, ObjectIterator endO,
                               PositionIterator beginP, PositionIterator endP,
                               const double angle)
{
    ObjectIterator iterO = beginO;
    PositionIterator iterP = beginP;

    for (; iterO != endO || iterP != endP; ++iterO, ++iterP) {
        Object* obj = iterO->get();
        Position* pos = iterP->get();
        Point3D center = pos->get();
        obj->rotateZ(center, angle);
    }
}
