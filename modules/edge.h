#ifndef AANDSD_EDGE_H
#define AANDSD_EDGE_H

// Ребро
struct Edge {
    int from;
    int to;
    double weight;
    bool operator<(Edge const& other) const;
};

#endif //AANDSD_EDGE_H
