#ifndef DATALOGPROJECT_NODE_H
#define DATALOGPROJECT_NODE_H
#include <iostream>
#include <set>
#include <sstream>

class Node {
private:
    set<int> adjacentNodeIDs;
//    int postOrder = 0;
    bool visit = false;

public:
    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }
    string toString() {
        stringstream out;
        string text;
        for (auto& it : adjacentNodeIDs) {
            out << "R" << it << ",";
        }
        text = out.str();
        if (!text.empty()) {text.erase(text.size()-1,1);} // remove last comma
        return text;
    }
//    void setPostOrder(int value) {
//        postOrder = value;
//    }
//    int getPostOrder() {
//        return postOrder;
//    }
    set<int> getEdges() {
        return adjacentNodeIDs;
    }
    void visited() {
        visit = true;
    }
    void unvisit() {
        visit = false;
    }
    bool hasvisit() {
        return visit;
    }

};



#endif //DATALOGPROJECT_NODE_H
