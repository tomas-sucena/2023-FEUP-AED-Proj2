#include "AirGraph.h"

AirGraph::AirGraph() {}

bool AirGraph::addVertex(Airport &a){
    return vertices.insert({a.getCode(), a}).second;
}

void AirGraph::addEdge(string airportA, string airportB, string airline){
    Airport& dest = vertices[airportB].value;
    Airline& a = airlineCodes[airline];

    vertices[airportA].adj.insert(Edge(dest, a));
}
