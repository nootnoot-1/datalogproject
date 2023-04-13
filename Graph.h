#ifndef DATALOGPROJECT_GRAPH_H
#define DATALOGPROJECT_GRAPH_H
#include <iostream>
#include <sstream>
#include <map>
#include <stack>

class Graph {
private:
    map<int,Node> nodes;
//    int post = 1;
    stack<int> postorder;
    vector<int> nodesvisited;

public:
    explicit Graph(unsigned int size) {
        for (long unsigned int nodeID = 0; nodeID < size; nodeID++) {
            nodes[nodeID] = Node();
        }
    }
    void clearVisit() {
        for (long unsigned int i=0; i<nodes.size(); ++i) {
            nodes.at(i).unvisit();
        }
    }
    Node at(int i) {return nodes.at(i);}
    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }
    string toString() {
        stringstream out;
        for (auto& pair : nodes) {
            int nodeID = pair.first;
            Node node = pair.second;
            out << "R" << nodeID << ":" << node.toString() << endl;
        }
        return out.str();
    }
    Graph reverse() {
        Graph g = Graph(nodes.size());
        for (long unsigned int nodeID = 0; nodeID < nodes.size(); ++nodeID) {
            for (const auto& it : nodes[nodeID].getEdges()) {
                g.addEdge(it, nodeID);
            }
        }
        return g;
    }
    void clearnodesvisited() {
        nodesvisited.clear();
    }
    vector<int> getnodesvisited() {
        return nodesvisited;
    }
    void dfs(int nodeID) {
        nodes[nodeID].visited();
        nodesvisited.push_back(nodeID);
        set<int> edges = nodes[nodeID].getEdges();
        if (!edges.empty()) {
            for (const auto& it : edges) {
                if (!nodes[it].hasvisit()){
                    dfs(it);
                }
            }
        }
//        nodes[nodeID].setPostOrder(post);
//        ++post;
//        postorder.push(nodeID);
    }
    void dfs1(int nodeID) {
        nodes[nodeID].visited();
        set<int> edges = nodes[nodeID].getEdges();
        if (!edges.empty()) {
            for (const auto& it : edges) {
                if (!nodes[it].hasvisit()){
                    dfs1(it);
                }
            }
        }
//        nodes[nodeID].setPostOrder(post);
//        ++post;
        postorder.push(nodeID);
    }
    stack<int> dfsForest() {
        for (long unsigned int i=0; i<nodes.size(); ++i) {
            if (!nodes[i].hasvisit()) {
                dfs1(i);
            }
        }
//        post = 1;
        return postorder;
    }

    void printvisit() {
        cout << endl << "NODES VISITED: " << endl;
        for (long unsigned int i=0; i<nodes.size(); ++i) {
            cout << "R" << i << ": ";
            if (nodes[i].hasvisit()) {
                cout << "Y" << endl;
            } else {cout << "N" << endl;}
        }
    }
//    void printPostOrder() {
//        cout << endl << "POSTORDER STACK:" << endl;
//        for (long unsigned int i=0; i<nodes.size(); ++i) {
//            cout << "R" << i << ": " << nodes[i].getPostOrder() << endl;
//        }
//        stack<int> temp = postorder;                                  //PRINTING THE STACK MADE BY dfsFOREST
//        for (long unsigned int i=0; i<postorder.size(); ++i) {
//            cout << temp.top() << endl;
//            temp.pop();
//        }
//    }

};

#endif //DATALOGPROJECT_GRAPH_H
