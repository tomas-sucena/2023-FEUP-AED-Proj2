#include "AirGraph.h"

#include <list>
#include <map>
#include <queue>
#include <unordered_set>

#include "data/Airline.h"
#include "data/Airport.h"

#define Path list<const AirGraph::Edge*>
#define uSet unordered_set
#define uMap unordered_map

/**
 * @brief Construct a new Air Graph:: Air Graph object
 */
AirGraph::AirGraph() = default;

/**
 * @brief adds a vertex to the AirGraph
 * @complexity O(1)
 * @param a Airport that will be stored in the vertex
 * @return 'true' if insertion occurs, otherwise 'false'
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
    auto it = edges.find({airportA, airportB});

    if (it != edges.end()){
        it->second->addAirline(airlineCodes[airline]);
        return;
    }

    // new edge
    Edge* e = new Edge(vertices[airportA].value, vertices[airportB].value, airlineCodes[airline]);

    vertices[airportA].adj.insert(e);
    edges[{airportA, airportB}] = e;
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
 * @brief returns the Airport whose code is passed as an argument
 * @param code code of the Airport
 * @return Airport
 */
Airport AirGraph::getAirport(const string& code){
    return vertices[code].value;
}

/**
 * @brief returns the flights you can take in an Airport
 * @param code code of the Airport
 * @return set<AirGraph::Edge*> with the edges (flights) of the Airport
 */
set<AirGraph::Edge*> AirGraph::getFlights(const string& code){
    return vertices[code].adj;
}

/**
 * @brief sets to 'false' the 'visited' parameter of all vertices
 * @complexity O(|V| + |E|)
 */
void AirGraph::reset(){
    for (auto& p : vertices){
        p.second.valid = true;
    }

    for (auto& p : edges){
        p.second->valid = true;
    }
}

/**
 * @brief checks if an edge contains at least one Airline that the user wants to use
 * @complexity O(|E|)
 * @param use codes of the Airlines that the user would like to use
 * @return 'true' if the edge is valid and 'false' otherwise
 */
void AirGraph::validateEdges(uSet<string> use){
    // no restrictions
    if (use.empty()){
        for (auto& p : edges){
            p.second->valid = true;
        }

        return;
    }

    for (auto& p : edges){
        Edge* e = p.second;
        e->valid = false;

        for (const Airline& a : e->airlines){
            if (use.find(a.getCode()) == use.end()) continue;

            // if an airline is found
            e->valid = true;
            break;
        }
    }
}

/**
 * @brief checks if a vertex should be traversed in the search functions
 * @complexity O(|V|)
 * @param use codes of the Airports that the user would like to use
 * @return 'true' if the vertex is valid and 'false' otherwise
 */
void AirGraph::validateVertices(uSet<string> use){
    // no restrictions
    if (use.empty()){
        for (auto& p : vertices){
            p.second.valid = true;
        }

        return;
    }

    for (auto& p : vertices){
        string code = p.second.value.getCode();

        p.second.valid = (use.find(code) != use.end());
    }
}

/**
 * @brief checks which vertices and edges are valid
 * @complexity O(|V| + |E|)
 * @param use array of two unordered_sets, both containing codes (of Airlines and Airports, respectively)
 */
void AirGraph::validate(uSet<string>* use){
    if (use == nullptr){
        validateEdges({});
        validateVertices({});

        return;
    }

    validateEdges(use[0]);
    validateVertices(use[1]);
}

/**
 * @brief implementation of the Depth-First Search algorithm, which iterates through all the vertices and edges
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport that is stored in the initial vertex
 */
void AirGraph::dfs(const string& airportA, const string& airportB, Path currPath, list<Path>& allPaths){
    Vertex& currV = vertices[airportA];
    currV.valid = false;

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

        currV.valid = true;
        return;
    }

    for (const Edge* e : currV.adj){
        if (!e->valid || !vertices[e->dest.getCode()].valid){
            continue;
        }

        currPath.push_back(e);
        dfs(e->dest.getCode(), airportB, currPath, allPaths);
        currPath.pop_back();
    }
}

/**
 * @brief implementation of the Depth-First Search algorithm, which iterates through all the vertices and edges
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport that is stored in the initial vertex
 * @param distance radius
 * @return container with all of the reachable Airports
 */
uSet<Airport> AirGraph::dfs(const string& airport, double distance){
    uSet<Airport> reached;
    if (distance <= 0) return reached;

    vertices[airport].valid = false;

    for (const Edge* e : vertices[airport].adj){
        if (!e->valid || !vertices[e->dest.getCode()].valid){
            continue;
        }

        reached.merge(dfs(e->dest.getCode(), distance - e->distance));
    }

    return reached;
}

/**
 * @brief implementation of the Breadth-First Search algorithm, which iterates through all the vertices and edges
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport which constitutes the starting point
 * @param flights number of flights
 * @return list<Airport> with the reachable Airports
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

            if (e->valid && vertices[w].valid) { // new vertex!
                unvisitedV.push(w);
                visitedV.push_back(w);

                vertices[w].valid = false;
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

    return res;
}

/**
 * @brief performs a Breadth-First Search to get the Airports you can reach in a certain number of flights
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport which constitutes the starting point
 * @param flights number of flights
 * @param use set of Airlines and Airports that the user would like to use
 * @return list<Airport> with the reachable Airports
 */
list<Airport> AirGraph::getReachableAirports(const string& airport, int flights, uSet<string>* use){
    validate(use);
    if (!vertices[airport].valid){
        return {};
    }

    const list<Airport>& reachable = bfs(airport, flights);
    reset();

    return reachable;
}

/**
 * @brief gets the Airports nearest the location defined by the pair (lat, lon)
 * @complexity O(|V|)
 * @param lat latitude
 * @param lon longitude
 * @param rad radius of search
 * @return map<double, string> containing Airports and their corresponding distance to the specified location
 */
map<double, string> AirGraph::getNearbyAirports(double lat, double lon, double rad){
    map<double, string> airports;

    for(auto &[key, val]:vertices){
        double dist = val.value.getDistance(lat, lon);
        if(dist <= rad){
            airports.insert({dist, val.value.getName()});
        }
    }

    return airports;
}

/**
 * @brief gets all the shortest paths from one Airport to another
 * @complexity O(|V| + |E|)
 * @param airportA code of the Airport which constitutes the starting point
 * @param airportB code of the Airport which constitutes the destination
 * @return list<Path> with the shortest paths
 */
list<Path> AirGraph::getPaths(const string& airportA, const string& airportB, uSet<string>* use){
    list<Path> allPaths;
    Path currPath;

    validate(use);
    if (!vertices[airportA].valid || !vertices[airportB].valid){
        reset();
        return {};
    }

    dfs(airportA, airportB, currPath, allPaths);
    reset();

    return allPaths;
}