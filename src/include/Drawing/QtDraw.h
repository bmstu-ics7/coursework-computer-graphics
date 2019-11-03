#ifndef __QTDRAW_H
#define __QTDRAW_H

#include "Drawer.h"

class QtDraw : public Drawer
{
public:
    QtDraw(QPainter& painter, const size_t w, const size_t h);
    void drawLine(const Point3D& a, const Point3D& b) override;
    void Wu(const Point3D& a, const Point3D& b);

private:
    int round(double x);

    QPainter& painter;
};

#endif // __QTDRAW_H
