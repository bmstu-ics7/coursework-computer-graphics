#ifndef __TRANSFORMMANAGER_H
#define __TRANSFORMMANAGER_H

#include "Manager.h"

class TransformManager : public Manager
{
public:
    TransformManager() { }

    void offset(ObjectIterator beginO, ObjectIterator endO,
                PositionIterator beginP, PositionIterator endP,
                const double dx, const double dy, const double dz);
    void scale(ObjectIterator beginO, ObjectIterator endO,
               PositionIterator beginP, PositionIterator endP,
               const double k);
    void rotateX(ObjectIterator beginO, ObjectIterator endO,
                 PositionIterator beginP, PositionIterator endP,
                 const double angle);
    void rotateY(ObjectIterator beginO, ObjectIterator endO,
                 PositionIterator beginP, PositionIterator endP,
                 const double angke);
    void rotateZ(ObjectIterator beginO, ObjectIterator endO,
                 PositionIterator beginP, PositionIterator endP,
                 const double angle);
};

#endif // __TRANSFORMMANAGER_H
