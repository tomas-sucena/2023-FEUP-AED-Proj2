#include "Graph.h"

Graph::Graph(bool dir){
    n = 0;
    this->hasDir = dir;
}

Graph::Graph(int nodes, bool dir){
    this->n = nodes;
    this->hasDir = dir;
}
