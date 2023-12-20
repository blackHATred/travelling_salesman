#ifndef AANDSD_POINT_H
#define AANDSD_POINT_H

// Точка
struct Point {
    double x;
    double y;
    Point();
    static double getDistance(const Point &p1, const Point & p2);
};

#endif //AANDSD_POINT_H
