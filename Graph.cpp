#include "Graph.h"

Graph::Graph(int n) {
    // TODO: Implement constructor
    numNodes = n;
    adjacencyList.resize(n);
}

void Graph::addEdge(int from, int to, int version, int distance) {
    // TODO: Implement addEdge
    bool found = false;
    for(int i = 0;i < adjacencyList[from].size();i++){
        if(adjacencyList[from][i].toNodeId == to){
            found = true;
            if(version < adjacencyList[from][i].version){
                adjacencyList[from][i].version = version;
                adjacencyList[from][i].distance = distance;
            }
            else if(version == adjacencyList[from][i].version && distance < adjacencyList[from][i].distance){
                adjacencyList[from][i].version = version;
                adjacencyList[from][i].distance = distance;
            }
            break;
        }
    }
    if(found == false){
        Edge newedge(to, version, distance);
        adjacencyList[from].push_back(newedge);
    }

    found = false;
    for(int i = 0;i < adjacencyList[to].size();i++){
        if(adjacencyList[to][i].toNodeId == from){
            found = true;
            if(version < adjacencyList[to][i].version){
                adjacencyList[to][i].version = version;
                adjacencyList[to][i].distance = distance;
            }
            else if(version == adjacencyList[to][i].version && distance < adjacencyList[to][i].distance){
                adjacencyList[to][i].version = version;
                adjacencyList[to][i].distance = distance;
            }
            break;
        }
    }
    if(found == false){
        Edge newedge(from, version, distance);
        adjacencyList[to].push_back(newedge);
    }
}

const std::vector<Edge>& Graph::getNeighbors(int nodeId) const {
    // TODO: Implement getNeighbors
    // Note: You must return the adjacency list of the given node.
    // This return is just a placeholder to compile.
    return adjacencyList[nodeId]; 
}

int Graph::getNumNodes() const {
    // TODO: Implement getNumNodes
    return numNodes;
}