#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Edge.h"

class Graph {
private:
    int numNodes;
    std::vector<std::vector<Edge> > adjacencyList; 

public:
    Graph(int n);
    void addEdge(int from, int to, int version, int distance);
    const std::vector<Edge>& getNeighbors(int nodeId) const;
    int getNumNodes() const;
};

#endif