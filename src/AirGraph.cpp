#include "AirGraph.h"

#include "data/Airline.h"
#include "data/Airport.h"

AirGraph::AirGraph() {}

/**
 * @brief adds a vertex to the AirGraph
 * @complexity O(1)
 * @param a Airport that will be stored in the vertex
 * @return true if insertion occurs, otherwise false
 */
bool AirGraph::addVertex(Airport &a){
    return vertices.insert({a.getCode(), a}).second;
}

/**
 * @brief adds an edge to a vertex of the AirGraph
 * @complexity O(1)
 * @param airportA code of the Airport which is stored in the source vertex
 * @param airportB code of the Airport which is stored in the destination vertex
 * @param airline Airline that establishes the connection between the Airports
 */
void AirGraph::addEdge(string airportA, string airportB, string airline){
    Airport& dest = vertices[airportB].value;
    Airline& a = airlineCodes[airline];
    double distance = vertices[airportA].value.getDistance(dest);

    vertices[airportA].adj.insert(Edge(dest, a, distance));
}

/**
 * @brief adds an Airline to the AirGraph
 * @complexity O(1)
 * @param a Airline that will be added
 * @return true if insertion occurs, otherwise false
 */
bool AirGraph::addAirline(Airline &a){
    return airlineCodes.insert({a.getCode(), a}).second;
}

/**
 * @brief
 * @complexity O(|V|+|E|)
 * @param airport code of the Airport that is stored in the initial vertex
 */
void AirGraph::dfs(string airport){
    Vertex v = vertices[airport];
    v.visited = true;

    for (Edge e : v.adj){
        Vertex w = vertices[e.dest.getCode()];

        if (!w.visited) dfs(w.value.getCode());
    }
}