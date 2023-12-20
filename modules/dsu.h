#include "vector"

#ifndef AANDSD_DSU_H
#define AANDSD_DSU_H

// Система непересекающихся множеств, за основу взят код с семинара синей группы (Крымов)
class DSU {
public:
    explicit DSU(int verticesCount);
    int findSet(int v);
    void unionSet(int v, int u);
private:
    std::vector<int> parent;
    std::vector<int> rank;
};

#endif //AANDSD_DSU_H
