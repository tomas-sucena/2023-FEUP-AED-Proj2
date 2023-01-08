#ifndef AIRPORTAED_AIRGRAPH_H
#define AIRPORTAED_AIRGRAPH_H

#include <iostream>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "data/Airline.h"
#include "data/Airport.h"

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
        uMap<double, string> getNearbyAirports(double lat, double lon, double rad);
        list<Airport> getReachableAirports(const string& airport, int flights, uSet<string>* use = nullptr);
        list<Path> getPaths(const string& airportA, const string& airportB, uSet<string>* use = nullptr);

        void reset();

        void validateEdges(uSet<string> use);
        void validateVertices(uSet<string> use);
        void validate(uSet<string>* use = nullptr);

        void dfs(const string& airportA, const string& airportB, Path currPath, list<Path>& allPaths);
        uSet<Airport> dfs(const string& airport, double distance);

        list<Airport> bfs(const string& airport, int flights);
};

#endif //AIRPORTAED_AIRGRAPH_H
