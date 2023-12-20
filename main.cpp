/*
 * Батовкин Александр
 * Задача 5 вариант 1 (Крускал):
   1 часть (яндекс контест):
    Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.
   2 часть:
    Найдите приближенное решение метрической неориентированной задачи коммивояжера в полном графе (на плоскости) с
    помощью минимального остовного дерева. Оцените качество приближения на случайном наборе точек, нормально
    распределенном на плоскости с дисперсией 1. Нормально распределенный набор точек получайте с помощью преобразования
    Бокса-Мюллера. При фиксированном N, количестве вершин графа, несколько раз запустите оценку качества приближения.
    Вычислите среднее значение и среднеквадратичное отклонение качества приближения для данного N. Запустите данный
    эксперимент для всех N в некотором диапазоне, например, [2, 10].
    Автоматизируйте запуск экспериментов.
 */
#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>
#include <climits>
#include <algorithm>
#include "modules/point.h"
#include "modules/dsu.h"
#include "modules/graph.h"


void test(){
    /*
    Алгоритм с семинара синих:
    1) Получаем N точек с помощью алгоритма Бокса-Мюллера:
     x = cos(2*pi*u) * sqrt(-2*ln(v))
     y = sin(2*pi*u) * sqrt(-2*ln(v))
     u, v =  rand() * 1.0 / RAND_MAX : это число от 0 до 1
    2) Перебором находим оптимальный путь С*
    3) Строим минимальное остовное дерево на графе п. 1
    4) Обходим, получаем С
    5) Считаем C / C*
    6) Запускаем 10 раз с n = 1
    7) x среднее = (x1 + ... + xn) / n (каждый из x - это результат из 5го пункта)
    8) сигма = sqrt( ((x1 - xср)^2 + ... + (xn - xср)^2) / n )
    9) повторить всё это для n = [2, 10]

     PS: по идее, в формуле для сигмы нужно делить не на n, а на n-1, но на семинаре была дана такая формула ¯\_(ツ)_/¯
    */
    for (int n = 2; n < 11; n++) {
        std::vector<double> x(10);
        for (int xi = 0; xi < 10; xi++) {
            // набор из n случайно сгенерированных точек с помощью алгоритма Бокса-Мюллера
            std::vector<Point> points(n);

            // из набора точек сделаем всевозможные попарные их комбинации
            Graph edges(1, n);
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++)
                    edges.add({i, j, Point::getDistance(points[i], points[j])});

            // из всевозможных способов обойти n точек находим самый выгодный полным перебором
            double minWeight = INT_MAX;
            std::vector<int> perm(n);
            for (int i = 0; i < n; i++) perm[i] = i;

            do {
                double weightCounter = 0;
                for (int i = 0; i < n - 1; i++)
                    weightCounter += edges.getEdges()[edges.findIndex(perm[i], perm[i + 1])].weight;
                int lastIndex = edges.findIndex(perm[n - 1], perm[0]); // Замыкаем цикл
                weightCounter += edges.getEdges()[lastIndex].weight;
                if (weightCounter < minWeight)
                    minWeight = weightCounter;
            } while (std::next_permutation(perm.begin(), perm.end()));

            // теперь считаем с помощью приближённого алгоритма на основе минимального остовного дерева
            auto tree = edges.kruskal();
            // полученное остовное дерево нужно обойти и посчитать весь путь тура коммивояжера
            auto tour = tree.getTour();
            double weightCounter = 0;
            for (int i = 0; i < tour.size() - 1; i++)
                weightCounter += edges.getEdges()[edges.findIndex(tour[i], tour[i + 1])].weight;
            int lastIndex = edges.findIndex(tour.back(), tour.front()); // замыкаем цикл
            weightCounter += edges.getEdges()[lastIndex].weight;

            x[xi] = weightCounter / minWeight;
            // теорема гласит, что тур коммивояжера, полученный по минимальному остовному дереву,
            // гарантированно хуже оптимального пути не более, чем в два раза
            assert(x[xi] <= 2);
        }

        std::cout << "* n = " << n << " --------------------------" << std::endl;
        double sum = 0;
        for (auto xi : x) sum += xi;
        double x_ = sum / 10;
        std::cout << "среднее (икс с чертой) = " << x_ << std::endl;
        sum = 0;
        for (auto xi : x) sum += (xi - x_) * (xi - x_);
        std::cout << "среднеквадратичное отклонение (сигма) = " << std::sqrt(sum / 10) << std::endl;
    }
}

int main() {
    test();
    return 0;
}