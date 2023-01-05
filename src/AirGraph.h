#ifndef AIRPORTAED_AIRGRAPH_H
#define AIRPORTAED_AIRGRAPH_H

#include <iostream>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "data/Airline.h"
#include "data/Airport.h"

#define Path list<Airport>

class AirGraph {
    private:
        struct Edge {
            Airport dest;
            unordered_set<Airline> airlines;
            double distance; // weight

            Edge(Airport& dest, Airline& airline, double distance) : dest(dest), distance(distance) {
                airlines.insert(airline);
            }

            bool operator<(const Edge& e) const{
                return (distance < e.distance);
            }
        };

        struct Vertex {
            Airport value;
            set<Edge> adj;
            bool visited = false;

            Vertex() = default;
            Vertex(Airport& value) : value(value) {}
        };

        unordered_map<string, Vertex> vertices;

        // for search purposes
        unordered_map<string, Airline> airlineCodes;

    public:
        // constructor
        AirGraph();

        // methods
        bool addVertex(Airport& a);
        void addEdge(const string& airportA, const string& airportB, const string& airline);
        bool addAirline(Airline& a);

        Airport getAirport(const string& code);
        set<Edge> getFlights(const string& code);

        void reset();
        void reset(const list<Airport>& visited_airports);
        void reset(const list<string>& visited_airports);

        void dfs(const string& airportA, const string& airportB, Path currPath, list<Path>& allPaths);
        unordered_set<Airport> dfs(const string& airport, double distance);

        list<Airport> bfs(const string& airport, int flights);

        list<list<Airport>> getPaths(const string& airportA, const string& airportB);
};


#endif //AIRPORTAED_AIRGRAPH_H
