#include "AirGraph.h"

#include <list>
#include <queue>

#include "data/Airline.h"
#include "data/Airport.h"

AirGraph::AirGraph() = default;

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
void AirGraph::dfs(const string& airportA, const string& airportB, Path currPath, list<Path>& allPaths){
    Vertex& currV = vertices[airportA];
    currV.visited = true;

    currPath.push_back(currV.value);

    // target found
    if (airportA == airportB){
        bool insert = (allPaths.empty() || allPaths.front().size() <= currPath.size());
        bool clear = (insert && currPath.size() < allPaths.front().size());

        if (clear){
            allPaths.clear();
        }

        if (insert){
            allPaths.push_back(currPath);
        }

        return;
    }

    for (const Edge& e : currV.adj){
        if (!vertices[e.dest.getCode()].visited){
            dfs(e.dest.getCode(), airportB, currPath, allPaths);
        }
    }

}

/**
 * @brief
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport that is stored in the initial vertex
 * @param distance radius
 * @return container with all of the reachable Airports
 */
unordered_set<Airport> AirGraph::dfs(const string& airport, double distance){
    unordered_set<Airport> reached;
    if (distance <= 0) return reached;

    vertices[airport].visited = true;

    for (const Edge& e : vertices[airport].adj){
        if (vertices[e.dest.getCode()].visited){
            continue;
        }

        reached.merge(dfs(e.dest.getCode(), distance - e.distance));
    }

    return reached;
}

/**
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport that is stored in the initial vertex
 * @param flights
 * @return
 */
list<Airport> AirGraph::bfs(const string& airport, int flights){
    list<Airport> res;

    queue<string> unvisitedV; // unvisited vertices
    unvisitedV.push(airport);

    list<string> visitedV = {airport};

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

list<list<Airport>> AirGraph::getPaths(const string& airportA, const string& airportB){
    list<list<Airport>> allPaths;
    list<Airport> currPath;

    dfs(airportA, airportB, currPath, allPaths);
    reset();

    return allPaths;
}
