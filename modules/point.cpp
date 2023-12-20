#include <random>
#include "point.h"
#include <cmath>

Point::Point() {
    // случайная генерация точки с помощью алгоритма Бокса-Мюллера
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::mt19937 gen(std::random_device{}());
    double u1 = dist(gen);
    double u2 = dist(gen);
    x = std::cos(2.0*3.141*u1) * std::sqrt(-2.0*std::log(u2));
    y = std::sin(2.0*3.141*u1) * std::sqrt(-2.0*std::log(u2));
}
double Point::getDistance(const Point &p1, const Point & p2){
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
