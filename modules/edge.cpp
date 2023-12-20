#include "edge.h"

bool Edge::operator<(const Edge &other) const {
    return weight < other.weight;
}