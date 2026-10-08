#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
    int toNodeId;
    int version;  
    int distance; 

    Edge();
    Edge(int to, int v, int d);

    bool operator<(const Edge& other) const;
};

#endif