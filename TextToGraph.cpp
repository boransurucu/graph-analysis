#include "TextToGraph.h"
#include <iostream>
#include <queue>
#include <stack>

TextToGraph::TextToGraph(const std::string& inputText) {
    // TODO: Implement constructor
    text = inputText;
    graph = NULL;
}

TextToGraph::~TextToGraph() {
    // TODO: Implement destructor
    delete graph;
}

void TextToGraph::constructGraph() {
    // TODO: Implement graph construction from text
    int version = 0;
    int newid = 0;
    std::string currentword = "";
    std::vector<int> currentsentence;
    std::vector<std::vector<int> > allsentences;

    for(int i = 0;i < text.size();i++){
        if(text[i] == ' '){
            if(currentword != ""){
                if (wordToId.count(currentword) == 0) {
                    wordToId[currentword] = newid;
                    idToWord.push_back(currentword);
                    newid++;
                }
                currentsentence.push_back(wordToId[currentword]);
                currentword = "";
            }
        }
        else if(text[i] == '.'){
            if(currentword != ""){
                if (wordToId.count(currentword) == 0) {
                    wordToId[currentword] = newid;
                    idToWord.push_back(currentword);
                    newid++;
                }
                currentsentence.push_back(wordToId[currentword]);
                currentword = "";
                allsentences.push_back(currentsentence);
                currentsentence.clear();
                version++;
            }
        }
        else{
            currentword += text[i];
        }
    }

    graph = new Graph(newid);
    for(int i = 0;i < allsentences.size();i++){
        for(int j = 0;j < allsentences[i].size();j++){
            for(int k = j + 1;k < allsentences[i].size();k++){
                graph->addEdge(allsentences[i][j], allsentences[i][k], i, k - j);
            }
        }
    }
}

void TextToGraph::printGraph() {
    // TODO: Implement printGraph
    std::vector<std::string> sortwords = idToWord;
    std::sort(sortwords.begin(), sortwords.end());

    for(int i = 0;i < sortwords.size();i++){
        std::string currentword = sortwords[i];
        int currentid = wordToId[currentword];

        std::cout<<currentword<<":";
        const std::vector<Edge>& neighbors = graph->getNeighbors(currentid);
        std::vector<std::pair<std::string, Edge> > sortneighbors;
        
        for(int j = 0; j < neighbors.size(); j++) {
            std::string neighborname = idToWord[neighbors[j].toNodeId];
            sortneighbors.push_back(std::make_pair(neighborname, neighbors[j]));
        }
        std::sort(sortneighbors.begin(), sortneighbors.end());

        for(int j = 0; j < sortneighbors.size(); j++) {
            std::cout << " " << sortneighbors[j].first << "(v:" << sortneighbors[j].second.version << ",d:" << sortneighbors[j].second.distance << ")";
        }
        std::cout<<std::endl;
    }
}

bool TextToGraph::isReachable(const std::string& source, const std::string& destination) {
    // TODO: Implement reachability
    if(source == destination){
        return true;
    }
    if(wordToId.count(source) == 0 || wordToId.count(destination) == 0){
        return false;
    }
    int sourceid = wordToId[source];
    int destinationid = wordToId[destination];
    if(sourceid == destinationid){
        return true;
    }

    std::vector<bool> isvisited(graph->getNumNodes(), false);
    std::queue<int> order;
    order.push(sourceid);
    isvisited[sourceid] = true;

    while(!order.empty()){
        int current = order.front();
        order.pop();
        if(current == destinationid){
            return true;
        }
        const std::vector<Edge>& neighbors = graph->getNeighbors(current);
        for(int i = 0;i < neighbors.size();i++){
            int neighborid = neighbors[i].toNodeId;
            if(isvisited[neighborid] == false){
                isvisited[neighborid] = true;
                order.push(neighborid);
            }
        }
    }

    return false;
}

bool TextToGraph::isReachableWithMaxVersion(const std::string& source, const std::string& destination, int maxVersion) {
    // TODO: Implement reachability with max version constraint
    if(source == destination){
        return true;
    }
    if(wordToId.count(source) == 0 || wordToId.count(destination) == 0){
        return false;
    }
    int sourceid = wordToId[source];
    int destinationid = wordToId[destination];
    if(sourceid == destinationid){
        return true;
    }

    std::vector<bool> isvisited(graph->getNumNodes(), false);
    std::queue<int> order;
    order.push(sourceid);
    isvisited[sourceid] = true;

    while(!order.empty()){
        int current = order.front();
        order.pop();
        if(current == destinationid){
            return true;
        }
        const std::vector<Edge>& neighbors = graph->getNeighbors(current);
        for(int i = 0;i < neighbors.size();i++){
            int neighborid = neighbors[i].toNodeId;
            if (neighbors[i].version > maxVersion) {
                continue;
            }
            if(isvisited[neighborid] == false){
                isvisited[neighborid] = true;
                order.push(neighborid);
            }
        }
    }

    return false;
}

void TextToGraph::customBFS(const std::string& startNode) {
    // TODO: Implement custom BFS
    if (wordToId.count(startNode) == 0) {
        return;
    }

    int startid = wordToId[startNode];
    std::vector<bool> isvisited(graph->getNumNodes(), false);
    std::queue<int> order;

    std::vector<std::string> specialrule;
    order.push(startid);
    isvisited[startid] = true;
    specialrule.push_back(startNode);

    while (!order.empty()) {
        int current = order.front();
        order.pop();

        const std::vector<Edge>& neighbors = graph->getNeighbors(current);
        std::vector<std::pair<int, std::string> > sortedneighbors;

        for (int i = 0; i < neighbors.size(); i++) {
            int neighborid = neighbors[i].toNodeId;
            // Sadece daha önce gitmediğimiz komşuları geçici listeye alıyoruz
            if (isvisited[neighborid] == false) {
                int dist = neighbors[i].distance;
                std::string word = idToWord[neighborid];
                sortedneighbors.push_back(std::make_pair(dist, word));
            }
        }

        std::sort(sortedneighbors.begin(), sortedneighbors.end());

        for (int i = 0; i < sortedneighbors.size(); i++) {
            std::string word = sortedneighbors[i].second;
            int id = wordToId[word];

            if (isvisited[id] == false) {
                isvisited[id] = true;
                order.push(id);
                specialrule.push_back(word);
            }
        }
    }

    for (int i = 0; i < specialrule.size(); i++) {
        if (i > 0) {
            std::cout << " ";
        }
        std::cout << specialrule[i];
    }
}

void TextToGraph::printArticulationPoints() {
    // TODO: Implement articulation points detection
    int n = graph->getNumNodes();
    if (n == 0) return;

    std::vector<int> discoverytime(n, -1);
    std::vector<int> lowesttime(n, -1);
    std::vector<bool> isarticulationpoint(n, false);

    std::vector<int> parentarr(n, -1);      
    std::vector<int> edgeindex(n, 0);       
    std::vector<int> childrencount(n, 0);   

    int timer = 1;

    for (int startnode = 0; startnode < n; startnode++) {
        if (discoverytime[startnode] != -1) {
            continue; 
        }

        std::stack<int> st;
        st.push(startnode);

        while (!st.empty()) {
            int start = st.top();

            if (discoverytime[start] == -1) {
                discoverytime[start] = lowesttime[start] = timer;
                timer++;
            }

            bool pushednewnode = false;
            const std::vector<Edge>& neighbors = graph->getNeighbors(start);

            while (edgeindex[start] < neighbors.size()) {
                int target = neighbors[edgeindex[start]].toNodeId;
                edgeindex[start]++;
                if (target == parentarr[start]) {
                    continue;
                }
                if (discoverytime[target] == -1) {
                    parentarr[target] = start;
                    childrencount[start]++;
                    st.push(target);
                    pushednewnode = true;
                    break; 
                }
                else {
                    lowesttime[start] = std::min(lowesttime[start], discoverytime[target]);
                }
            }

            if (pushednewnode == false) {
                st.pop(); 
                int parent = parentarr[start];

                if (parent != -1) {
                    lowesttime[parent] = std::min(lowesttime[parent], lowesttime[start]);
                    if (parentarr[parent] == -1 && childrencount[parent] > 1) {
                        isarticulationpoint[parent] = true;
                    }
                    else if (parentarr[parent] != -1 && lowesttime[start] >= discoverytime[parent]) {
                        isarticulationpoint[parent] = true;
                    }
                }
            }
        }
    }

    std::vector<std::string> apwords;
    for (int i = 0; i < n; i++) {
        if (isarticulationpoint[i] == true) {
            apwords.push_back(idToWord[i]);
        }
    }

    std::sort(apwords.begin(), apwords.end());
    for (int i = 0; i < apwords.size(); i++) {
        std::cout << apwords[i] << std::endl;
    }
}


void TextToGraph::printConnectedComponents() {
    // TODO: Implement connected components identification
    std::vector<bool> isvisited(graph->getNumNodes(), false);
    int counter = 1;
    std::vector<std::string> sortwords = idToWord;
    std::sort(sortwords.begin(), sortwords.end());

    for(int i = 0;i < sortwords.size();i++){
        std::string currentword = sortwords[i];
        int currentid = wordToId[currentword];
        if(isvisited[currentid] == false){
            std::vector<std::string> allwords;
            std::queue<int> order;
            isvisited[currentid] = true;
            order.push(currentid);
            allwords.push_back(currentword);

            while(!order.empty()){
                int current = order.front();
                order.pop();
                const std::vector<Edge>& neighbors = graph->getNeighbors(current);
                for(int j = 0;j < neighbors.size();j++){
                    int neighborid = neighbors[j].toNodeId;
                    if(isvisited[neighborid] == false){
                        isvisited[neighborid] = true;
                        order.push(neighborid);
                        allwords.push_back(idToWord[neighborid]);
                    }
                }
            }
            std::vector<std::string> sortall = allwords;
            std::sort(sortall.begin(), sortall.end());
            std::cout << "Component " << counter << ":";

            for(int k = 0;k < sortall.size();k++){
                std::cout<<" "<<sortall[k];
            }
            std::cout<<std::endl;
            counter++;
        }
    }
}