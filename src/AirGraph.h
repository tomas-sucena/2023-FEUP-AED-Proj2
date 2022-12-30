#ifndef AIRPORTAED_AIRGRAPH_H
#define AIRPORTAED_AIRGRAPH_H

#include <set>
#include <unordered_map>
#include <unordered_set>

#include "data/Airline.h"
#include "data/Airport.h"

class AirGraph {
    private:
        struct Edge {
            Airport dest;
            unordered_set<Airline> airlines;
            double distance; // weight

            Edge(Airport& dest, Airline& airline) : dest(dest) {
                airlines.insert(airline);
            }

            bool operator<(const Edge& e) const{
                return (distance < e.distance);
            }
        };

        struct Vertex {
            Airport value;
            set<Edge> adj;

            Vertex() {};
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
        void addEdge(string airportA, string airportB, string airline);
};


#endif //AIRPORTAED_AIRGRAPH_H
