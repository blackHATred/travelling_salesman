#include "dsu.h"

DSU::DSU(int verticesCount) {
    parent.resize(verticesCount);
    rank.resize(verticesCount, 1);
    for (int i = 0; i < verticesCount; parent[i++] = i);
}

int DSU::findSet(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = findSet(parent[v]);
}

void DSU::unionSet(int v, int u) {
    int v_set = findSet(v);
    int u_set = findSet(u);

    int rank_v = rank[v_set];
    int rank_u = rank[u_set];

    if (rank_u > rank_v){
        parent[v_set] = u_set;
        rank[v_set] += rank[u_set];
    } else {
        parent[u_set] = v_set;
        rank[u_set] += rank[v_set];
    }
}

