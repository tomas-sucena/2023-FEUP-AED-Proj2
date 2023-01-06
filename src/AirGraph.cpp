#include "AirGraph.h"

#include <list>
#include <queue>
#include <unordered_set>

#include "data/Airline.h"
#include "data/Airport.h"

#define uSet unordered_set
#define Path list<Airport>

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
void AirGraph::addEdge(const string& airportA, const string& airportB, const string& airline){
    Airport& dest = vertices[airportB].value;
    Airline& a = airlineCodes[airline];
    double distance = vertices[airportA].value.getDistance(dest);

    // create the edge
    Edge* e = new Edge(dest, a, distance);

    vertices[airportA].adj.insert(e);
    edges.insert(e);
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

set<AirGraph::Edge*> AirGraph::getFlights(const string& code){
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

    for (Edge* e : edges){
        e->valid = true;
    }
}

/**
 * @brief sets to 'false' the 'visited' parameter of the vertices whose Airport is in visited_airports
 * @complexity O(|V|)
 * @param visited_airports list of the visited Airports
 */
void AirGraph::reset(const list<Airport>& visited_airports){
    for (const Airport& a : visited_airports){
        vertices[a.getCode()].visited = false;
    }
}

/**
 * @brief sets to 'false' the 'visited' parameter of the vertices whose Airport code is in visited_airports
 * @complexity O(|V|)
 * @param visited_airports list of the codes of the visited Airports
 */
void AirGraph::reset(const list<string>& visited_airports){
    for (const string& code : visited_airports){
        vertices[code].visited = false;
    }
}

/**
 * @brief checks if an edge contains at least one Airline that the user wants to use
 * @param airlines codes of the Airlines that the user would like to use
 * @return 'true' if the edge is valid or 'false' otherwise
 */
void AirGraph::validateEdges(uSet<string>* airlines){
    // no restrictions
    if (airlines == nullptr){
        for (Edge* e : edges){
            e->valid = true;
        }

        return;
    }

    for (Edge* e : edges){
        e->valid = false;

        for (const Airline& a : e->airlines){
            // if an airline is found
            if (airlines->find(a.getCode()) != airlines->end()){
                e->valid = true;
                break;
            }
        }
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
        bool insert = (allPaths.empty() || currPath.size() <= allPaths.front().size());
        bool clear = (insert && currPath.size() < allPaths.front().size());

        if (clear){
            allPaths.clear();
        }

        if (insert){
            allPaths.push_back(currPath);
        }

        currV.visited = false;
        return;
    }

    for (const Edge* e : currV.adj){
        if (!vertices[e->dest.getCode()].visited && e->valid){
            dfs(e->dest.getCode(), airportB, currPath, allPaths);
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
uSet<Airport> AirGraph::dfs(const string& airport, double distance){
    uSet<Airport> reached;
    if (distance <= 0) return reached;

    vertices[airport].visited = true;

    for (const Edge* e : vertices[airport].adj){
        if (vertices[e->dest.getCode()].visited){
            continue;
        }

        reached.merge(dfs(e->dest.getCode(), distance - e->distance));
    }

    return reached;
}

/**
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport which constitutes the starting point
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
        for (const Edge* e : vertices[currV].adj) {
            string w = e->dest.getCode();

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

/**
 * @brief gets all the shortest paths from one Airport to another
 * @complexity O(|V| + |E|)
 * @param airportA code of the Airport which constitutes the starting point
 * @param airportB code of the Airport which constitutes the destination
 * @return list with the shortest paths
 */
list<Path> AirGraph::getPaths(const string& airportA, const string& airportB, uSet<string>* airlines){
    list<Path> allPaths;
    Path currPath;

    validateEdges(airlines);
    dfs(airportA, airportB, currPath, allPaths);
    reset();

    return allPaths;
}
