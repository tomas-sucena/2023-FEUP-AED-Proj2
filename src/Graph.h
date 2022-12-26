#ifndef AIRPORTAED_GRAPH_H
#define AIRPORTAED_GRAPH_H

#include <list>
#include <vector>

using namespace std;

class Graph {
    private:
        struct Edge {
            int dest;
            int weight;
        };
        struct Node {
            list<Edge> adj;
            bool visited;
        };
        int n;
        bool hasDir;
        vector<Node> nodes;
    public:
        // constructor
        explicit Graph(bool dir = false);
        Graph(int nodes, bool dir = false);

        // method
        void addEdge(int src, int dest, int weight = 1);
};


#endif //AIRPORTAED_GRAPH_H
