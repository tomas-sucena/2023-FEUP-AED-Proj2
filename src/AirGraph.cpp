#include "AirGraph.h"

#include <list>
#include <queue>
#include <stack>

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

Airport AirGraph::getAirport(const string& code){
    return vertices[code].value;
}

set<AirGraph::Edge> AirGraph::getFlights(const string& code){
    return vertices[code].adj;
}

/**
 * @brief sets to 'false' the 'visited' parameter of all vertices
 * @complexity O(|V|)
 */
void AirGraph::reset(){
    for (auto& p : vertices){
        p.second.visited = false;
    }
}

/**
 * @brief sets to 'false' the 'visited' parameter of some vertices
 * @complexity O(|V|)
 * @param visited_airports list of the codes of the visited Airports
 */
void AirGraph::reset(const list<string>& visited_airports){
    for (const string& code : visited_airports){
        vertices[code].visited = false;
    }
}

/**
 * @brief
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport that is stored in the initial vertex
 */
void AirGraph::dfs(string& airport){
    stack<string> unvisitedV;
    unvisitedV.push(airport);

    list<string> visitedV; // visited vertices

    while (!unvisitedV.empty()){
        string currV = unvisitedV.top();

        unvisitedV.pop();
        visitedV.push_back(currV);

        Vertex& v = vertices[currV];
        if (!v.visited){
            v.visited = true;

            for (const Edge& e : v.adj){
                unvisitedV.push(e.dest.getCode());
            }
        }
    }

    // reset all the visited vertices
    reset(visitedV);
}

/**
 * @brief
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport that is stored in the initial vertex
 */
list<Airport> AirGraph::bfs(string& start, int flights){
    list<Airport> res;

    queue<string> unvisitedV; // unvisited vertices
    unvisitedV.push(start);

    list<string> visitedV = {start};

    int currNeighbors = 1, nextNeighbors = 0;

    while (flights > 0 && !unvisitedV.empty()){
        string currV = unvisitedV.front(); // current vertex
        unvisitedV.pop ();

        //cout << currV << " "; // show vertex order
        for (const Edge& e : vertices[currV].adj) {
            string w = e.dest.getCode();

            if (!vertices[w].visited) { // new vertex!
                unvisitedV.push(w);
                visitedV.push_back(w);

                vertices[w].visited = true;
                res.push_back(vertices[w].value);

                nextNeighbors++;
            }
        }

        if (!--currNeighbors){
            flights--;

            currNeighbors = nextNeighbors;
            nextNeighbors = 0;
        }
    }

    // reset all the visited vertices
    reset(visitedV);

    return res;
}

