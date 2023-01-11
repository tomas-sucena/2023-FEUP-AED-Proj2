#ifndef AIRPORTAED_AIRGRAPH_H
#define AIRPORTAED_AIRGRAPH_H

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "Airline.h"
#include "Airport.h"

#define Path list<const AirGraph::Edge*>
#define uSet unordered_set
#define uMap unordered_map

// taken from https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-pairs-in-c/
namespace std {
    template <typename T, typename U>
    struct hash<pair<T, U>> {
        size_t operator()(const pair<string, string>& p) const{
            auto hash1 = hash<T>{}(p.first);
            auto hash2 = hash<U>{}(p.second);

            return (hash1 == hash2) ? hash1 : (hash1 ^ hash2);
        }
    };
}

class AirGraph {
    private:
        friend class Helpy;

        struct Edge {
            Airport src; // used for printing
            Airport dest;
            uSet<Airline> airlines;
            double distance;
            bool valid = true;

            Edge(Airport& src, Airport& dest, Airline& airline) : src(src), dest(dest) {
                airlines.insert(airline);
                distance = src.getDistance(dest);
            }

            bool addAirline(Airline& airline){
                return airlines.insert(airline).second;
            }

            bool operator<(const Edge& e) const{
                return (distance < e.distance);
            }
        };

        struct Vertex {
            Airport value;
            set<Edge*> adj;
            bool valid = true;

            Vertex() = default;
            Vertex(Airport& value) : value(value) {}
        };

        uMap<string, Vertex> vertices;
        uMap<pair<string, string>, Edge*> edges;
        uMap<string, Airline> airlineCodes; // for search purposes

    public:
        // constructor
        AirGraph();

        // methods
        bool addVertex(Airport& a);
        void addEdge(const string& airportA, const string& airportB, const string& airline);
        bool addAirline(Airline& a);

        Airport getAirport(const string& code);
        set<Edge*> getFlights(const string& code);
        map<double, string> getNearbyAirports(double lat, double lon, double rad);

        void reset();

        void validateEdges(uSet<string> use);
        void validateVertices(uSet<string> use);
        void validate(uSet<string>* use = nullptr);

        list<Path> bfs(const string& airportA, const string& airportB);
        uMap<Airport, double> bfs(const string& airport, double distance);
        list<pair<Airport, int>> bfs(const string& airport, int flights);

        list<Path> getPaths(const string& airportA, const string& airportB, uSet<string>* use = nullptr);
        uMap<Airport, double> getReachableAirports(const string& airport, double distance, uSet<string>* use = nullptr);
        list<pair<Airport, int>> getReachableAirports(const string& airport, int flights, uSet<string>* use = nullptr);
};

#endif //AIRPORTAED_AIRGRAPH_H
