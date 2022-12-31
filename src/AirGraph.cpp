#include "AirGraph.h"

AirGraph::AirGraph() {}

bool AirGraph::addVertex(Airport &a){
    return vertices.insert({a.getCode(), a}).second;
}

void AirGraph::addEdge(string airportA, string airportB, string airline){
    Airport& dest = vertices[airportB].value;
    Airline& a = airlineCodes[airline];
    double distance = vertices[airportA].value.getDistance(dest);

    vertices[airportA].adj.insert(Edge(dest, a, distance));
}

bool AirGraph::addAirline(Airline &a){
    return airlineCodes.insert({a.getCode(), a}).second;
}

void AirGraph::dfs(string airport){
    Vertex v = vertices[airport];
    v.visited = true;

    for (Edge e : v.adj){
        Vertex w = vertices[e.dest.getCode()];

        if (!w.visited) dfs(w.value.getCode());
    }
}