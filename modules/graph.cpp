#include "graph.h"
#include "stack"
#include <algorithm>

Graph::Graph(int size, int v) : vertices_count(v) {
    edges.reserve(size);
}

void Graph::add(Edge edge){
    edges.push_back(edge);
}

std::vector<Edge> Graph::getEdges(){
    return edges;
}

Graph Graph::kruskal() {
    // минимальное остовное дерево
    Graph tree(vertices_count-1, vertices_count);
    std::sort(edges.begin(), edges.end());

    DSU dsu(vertices_count);

    for (auto& edge : edges) {
        int v = dsu.findSet(edge.from);
        int u = dsu.findSet(edge.to);
        if (v != u) {
            dsu.unionSet(v, u);
            tree.add(edge);
        }
    }
    return tree;
}

int Graph::findIndex(const int p1, const int p2){
    // индекс пути из точки с индексом p1 в точку с индексом p2
    for (int i = 0; i < edges.size(); i++)
        if ((edges[i].from == p1 && edges[i].to == p2) || (edges[i].from == p2 && edges[i].to == p1)) return i;
    return -1;
}

void Graph::traverseTree(int vertex, std::vector<bool>& visited, std::vector<int>& tour) {
    // обход пути для составления тура коммивояжера на основе минимального остовного дерева
    std::stack<int> s;
    s.push(vertex);

    while (!s.empty()) {
        int v = s.top();
        s.pop();

        if (!visited[v]) {
            visited[v] = true;
            tour.push_back(v);
        }

        for (const auto& edge : edges) {
            if (edge.from == v && !visited[edge.to]) {
                s.push(edge.to);
            } else if (edge.to == v && !visited[edge.from]) {
                s.push(edge.from);
            }
        }
    }
}

std::vector<int> Graph::getTour() {
    std::vector<int> tour;
    std::vector<bool> visited(vertices_count, false);

    // начнем обход из первой вершины, хотя можно выбрать любую
    traverseTree(0, visited, tour);

    return tour;
}
