#ifndef TEXTTOGRAPH_H
#define TEXTTOGRAPH_H

#include <string>
#include <vector>
#include <map>
#include "Graph.h"
#include <algorithm>

class TextToGraph {
private:
    std::string text;
    std::map<std::string, int> wordToId;
    std::vector<std::string> idToWord; 
    Graph* graph;

public:
    TextToGraph(const std::string& inputText);
    ~TextToGraph();

    void constructGraph();
    void printGraph();

    bool isReachable(const std::string& source, const std::string& destination);
    bool isReachableWithMaxVersion(const std::string& source, const std::string& destination, int maxVersion);
    void customBFS(const std::string& startNode);
    void printArticulationPoints();
    void printConnectedComponents();
};

#endif