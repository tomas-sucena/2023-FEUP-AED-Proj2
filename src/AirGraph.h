#ifndef AIRPORTAED_AIRGRAPH_H
#define AIRPORTAED_AIRGRAPH_H

#include <string>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "Airline.h"
#include "Airport.h"

using namespace std;

class AirGraph {
    private:
        struct Flight {
            Airport dest;
            unordered_set<Airline> airlines;
            double distance; // weight

            Flight(Airport dest, Airline airline) : dest(dest) {
                airlines.insert(airline);
            }

            bool operator<(const Flight& f) const{
                return (distance < f.distance);
            }
        };

        unordered_map<Airport, set<Flight>> nodes;

        // for search purposes
        unordered_map<string, Airport> airportCodes;
        unordered_map<string, Airline> airlineCodes;

    public:
        // constructor
        AirGraph(list<Airport>* airports = nullptr);

        // methods
        void addFlight(string src, string dest, string airline);
};

#endif //AIRPORTAED_AIRGRAPH_H
