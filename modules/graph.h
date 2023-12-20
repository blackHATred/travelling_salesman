#include "edge.h"
#include "vector"
#include "dsu.h"
#ifndef AANDSD_GRAPH_H
#define AANDSD_GRAPH_H

// Граф на основе множества рёбер
struct Graph {
private:
    std::vector<Edge> edges;
    int vertices_count;
public:
    explicit Graph(int size, int v);
    void add(Edge edge);
    std::vector<Edge> getEdges();
    Graph kruskal();
    int findIndex(int p1, int p2);
    void traverseTree(int vertex, std::vector<bool>& visited, std::vector<int>& tour);
    std::vector<int> getTour();
};

#endif //AANDSD_GRAPH_H
