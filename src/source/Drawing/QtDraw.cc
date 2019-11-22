#include "Drawing/QtDraw.h"

QtDraw::QtDraw(QPainter& painter, const size_t w, const size_t h, Camera camera)
    : Drawer(w, h, camera), painter(painter){ }

int QtDraw::round(double x)
{
    int minus = x > 0 ? 1 : -1;
    return int(x + 0.5 * minus);
}

void QtDraw::drawLine(const Point3D& a, const Point3D& b)
{
    painter.drawLine(int(w / 2) + round(a.x()),
                     int(h / 2) + round(a.y()),
                     int(w / 2) + round(b.x()),
                     int(h / 2) + round(b.y()));
}
