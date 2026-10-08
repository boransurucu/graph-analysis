#include "Edge.h"

Edge::Edge() {
    // TODO: Implement default constructor
    toNodeId = 0;
    version = 0;
    distance = 0;
}

Edge::Edge(int to, int v, int d) {
    // TODO: Implement parameterized constructor
    toNodeId = to;
    version = v;
    distance = d;
}

bool Edge::operator<(const Edge& other) const {
    // TODO: Implement comparison for priority queue
    if(this->version < other.version){
        return true;
    }
    else if(this->version == other.version && this->distance < other.distance){
        return true;
    }
    return false;
}