#ifndef AIRPORTAED_GRAPH_H
#define AIRPORTAED_GRAPH_H

#include <list>
#include <unordered_set>

using namespace std;

template <typename T, typename U = int>
class Graph {
    private:
        struct Edge {
            T dest;
            U weight;

            Edge(T dest, U weight) : dest(dest), weight(weight) {}
        };

        struct Node {
            T val;
            list<Edge> adj;
            bool visited;

            Node(T val) : val(val) {}
            Node(T val, list<Edge> adj) : val(val), adj(adj) {}

            bool operator==(const Node& n) const{
                return (val == n.val);
            }
        };

        struct NodeHash {
            size_t operator()(const Node& n) const{
                return hash<T>()(n.val);
            }
        };

        unordered_set<Node, NodeHash> nodes;
        bool hasDir;

    public:
        // constructor
        explicit Graph(bool hasDir = false);

        // methods
        void addNode(T val);

        bool addEdge(T src, T dest, U weight);
        bool removeEdge(T src, T dest);
};


template<typename T, typename U>
Graph<T, U>::Graph(bool hasDir) : hasDir(hasDir) {}

template<typename T, typename U>
void Graph<T, U>::addNode(T val){
    nodes.insert(Node(val));
}

template<typename T, typename U>
bool Graph<T, U>::addEdge(T src, T dest, U weight){
    auto nodeIt = nodes.find(src);

    // verify if the node exists
    if (nodeIt == nodes.end()){
        return false;
    }

    Node n(nodeIt->val, nodeIt->adj);
    n.adj.push_back(Edge(dest, weight));

    nodes.erase(nodeIt);
    nodes.insert(n);

    return true;
}

template<typename T, typename U>
bool Graph<T, U>::removeEdge(T src, T dest){
    auto nodeIt = nodes.find(src);

    // verify if the node exists
    if (nodeIt == nodes.end()){
        return false;
    }

    Node n(nodeIt->val, nodeIt->adj);

    bool found = false;
    for (auto it = n.adj.begin(); it != n.adj.end(); it++){
        if (it->dest == dest){
            n.adj.erase(it);
            found = true;

            break;
        }
    }

    nodes.erase(nodeIt);
    nodes.insert(n);

    return found;
}

#endif //AIRPORTAED_GRAPH_H
