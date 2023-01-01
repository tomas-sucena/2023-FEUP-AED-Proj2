#ifndef AIRPORTAED_AIRGRAPH_H
#define AIRPORTAED_AIRGRAPH_H

#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <queue>

#include "data/Airline.h"
#include "data/Airport.h"

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
            bool visited;

            Vertex() = default;
            Vertex(Airport& value) : value(value) {}
        };

        unordered_map<string, Vertex> vertices;

        // for search purposes
        unordered_map<string, Airline> airlineCodes;

        vector<string> visited_airports;

    public:
        // constructor
        AirGraph();

        // methods
        bool addVertex(Airport& a);
        void addEdge(string airportA, string airportB, string airline);
        bool addAirline(Airline& a);
        Airport getAirport(string code);

        void printFlights(string code);

        void dfs(string start);
        void bfs(string start, int y);
};


#endif //AIRPORTAED_AIRGRAPH_H
