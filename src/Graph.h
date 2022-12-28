#ifndef AIRPORTAED_GRAPH_H
#define AIRPORTAED_GRAPH_H

#include <list>
#include <vector>

using namespace std;

template <typename T, typename U = int> // T -> stored type, U -> weight
class Graph {
    private:
        struct Edge {
            int dest;
            U weight;

            Edge(int dest, U weight) : dest(dest), weight(weight) {}
        };

        struct Node {
            T val;
            list<Edge> adj;
            bool visited;

            Node(T val) : val(val), visited(false) {}
        };

        bool hasDir;
        vector<Node> nodes;

    public:
        // constructor
        explicit Graph(bool hasDir = false);

        // methods
        void addNode(T val);
        bool setValue(int n, T val);

        bool addEdge(int src, int dest, U weight);
        bool removeEdge(int src, int dest);
};


template <typename T, typename U>
Graph<T, U>::Graph(bool hasDir) : hasDir(hasDir) {}

template <typename T, typename U>
void Graph<T, U>::addNode(T val){
    nodes.push_back(Node(val));
}

template <typename T, typename U>
bool Graph<T, U>::setValue(int n, T val){
    // verify if the node exists
    if (n < 1 || n > nodes.size()){
        return false;
    }

    nodes[n].val = val;
    return true;
}

template <typename T, typename U>
bool Graph<T, U>::addEdge(int src, int dest, U weight) {
    // verify if the nodes exist
    if (src < 1 || src > nodes.size() || dest < 1 || dest > nodes.size()){
        return false;
    }

    nodes[src].adj.push_back(Edge(dest, weight));
    return true;
}

template <typename T, typename U>
bool Graph<T, U>::removeEdge(int src, int dest) {
    // verify if the nodes exist
    if (src < 1 || src > nodes.size() || dest < 1 || dest > nodes.size()){
        return false;
    }

    for (auto it = nodes[src].adj.begin(); it != nodes[src].adj.end(); it++){
        if (it->dest == dest){
            nodes[src].adj.erase(it);
            return true;
        }
    }

    return false;
}

#endif //AIRPORTAED_GRAPH_H
