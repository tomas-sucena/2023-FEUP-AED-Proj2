#include "AirGraph.h"

#include <list>
#include <map>
#include <queue>
#include <unordered_set>

#include "Airline.h"
#include "Airport.h"

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
        if (dist <= rad){
            airports.insert({dist, val.value.getName()});
        }
    }

    return airports;
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
 * @brief implementation of the Breadth-First Search algorithm that returns the shortest paths (in terms of flights) from an Airport to another
 * @param airportA code of the Airport which constitutes the starting point
 * @param airportB code of the Airport which constitutes the destination
 * @return list<Path> with the shortest paths
 */
list<Path> AirGraph::bfs(const string& airportA, const string& airportB){
    list<Path> allPaths = {{}};

    queue<string> unvisitedV; // unvisited vertices
    unvisitedV.push(airportA);

    while (!unvisitedV.empty()){
        string code = unvisitedV.front();
        unvisitedV.pop();

        // target found
        if (code == airportB) break;

        Vertex& currV = vertices[code];
        currV.valid = false;

        Path currPath = allPaths.front();

        for (const Edge* e : currV.adj){
            if (!e->valid || !vertices[e->dest.getCode()].valid){
                continue;
            }

            unvisitedV.push(e->dest.getCode());

            currPath.push_back(e);
            allPaths.push_back(currPath);
            currPath.pop_back();
        }

        allPaths.pop_front();
    }

    // eliminate all undesirable paths
    auto it = allPaths.begin();
    int minPathSize = (int) it++->size();

    while (it != allPaths.end()){
        if (it->size() > minPathSize || it->back()->dest.getCode() != airportB){
            it = allPaths.erase(it);
            continue;
        }

        it++;
    }

    return allPaths;
}

/**
 * @brief implementation of the Breadth-First Search algorithm that returns the reachable Airports in a given flight distance
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport that is stored in the initial vertex
 * @param distance flight distance (in km)
 * @param travelled number of kilometers travelled
 * @return container with all of the reachable Airports and their respective flight distance from the starting point
 */
uMap<Airport, double> AirGraph::bfs(const string& airport, double distance){
    uMap<Airport, double> reached;

    queue<string> unvisitedV; // unvisited vertices
    unvisitedV.push(airport);

    queue<double> travelled;
    travelled.push(0);

    while (!unvisitedV.empty()){
        Vertex& currV = vertices[unvisitedV.front()];
        unvisitedV.pop();

        currV.valid = false;

        double currDist = travelled.front();
        reached.insert({currV.value, currDist});

        for (const Edge* e : currV.adj){
            bool validPath = e->valid && vertices[e->dest.getCode()].valid;
            bool validDistance = currDist + e->distance <= distance;

            if (!validPath || !validDistance){
                continue;
            }

            unvisitedV.push(e->dest.getCode());
            travelled.push(currDist + e->distance);
        }

        travelled.pop();
    }

    return reached;
}

/**
 * @brief implementation of the Breadth-First Search algorithm that returns the reachable Airports in a given number of flights
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport which constitutes the starting point
 * @param flights number of flights
 * @return container with the reachable Airports and the number of flights it took to reach them
 */
list<pair<Airport, int>> AirGraph::bfs(const string& airport, int flights){
    list<pair<Airport, int>> res = {{vertices[airport].value, 0}};
    vertices[airport].valid = false;

    queue<string> unvisitedV; // unvisited vertices
    unvisitedV.push(airport);

    int currNeighbors = 1, nextNeighbors = 0;
    int currFlight = 1;

    while (flights > 0 && !unvisitedV.empty()){
        string currV = unvisitedV.front(); // current vertex
        unvisitedV.pop ();

        for (const Edge* e : vertices[currV].adj) {
            string w = e->dest.getCode();

            if (e->valid && vertices[w].valid) { // new vertex!
                unvisitedV.push(w);

                vertices[w].valid = false;
                res.push_back({vertices[w].value, currFlight});

                nextNeighbors++;
            }
        }

        if (!--currNeighbors){
            flights--;
            currFlight++;

            currNeighbors = nextNeighbors;
            nextNeighbors = 0;
        }
    }

    return res;
}

/**
 * @brief gets all the shortest paths from one Airport to another
 * @complexity O(|V| + |E|)
 * @param airportA code of the Airport which constitutes the starting point
 * @param airportB code of the Airport which constitutes the destination
 * @return list<Path> with the shortest paths
 */
list<Path> AirGraph::getPaths(const string& airportA, const string& airportB, uSet<string>* use){
    validate(use);
    if (!vertices[airportA].valid || !vertices[airportB].valid){
        reset();
        return {};
    }

    list<Path> allPaths = bfs(airportA, airportB);
    reset();

    return allPaths;
}

/**
 * @brief performs a Breadth-First Search to get the Airports you can reach within a certain flight distance
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport which constitutes the starting point
 * @param distance flight distance
 * @param use set of Airlines and Airports that the user would like to use
 * @return list<Airport> with the reachable Airports
 */
uMap<Airport, double> AirGraph::getReachableAirports(const string& airport, double distance, uSet<string>* use){
    validate(use);
    if (!vertices[airport].valid){
        return {};
    }

    const uMap<Airport, double>& reachable = bfs(airport, distance);
    reset();

    return reachable;
}

/**
 * @brief performs a Breadth-First Search to get the Airports you can reach in a certain number of flights
 * @complexity O(|V| + |E|)
 * @param airport code of the Airport which constitutes the starting point
 * @param flights number of flights
 * @param use set of Airlines and Airports that the user would like to use
 * @return list<Airport> with the reachable Airports
 */
list<pair<Airport, int>> AirGraph::getReachableAirports(const string& airport, int flights, uSet<string>* use){
    validate(use);
    if (!vertices[airport].valid){
        return {};
    }

    const list<pair<Airport, int>>& reachable = bfs(airport, flights);
    reset();

    return reachable;
}