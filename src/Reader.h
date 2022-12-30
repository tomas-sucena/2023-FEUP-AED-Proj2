#ifndef AIRPORTAED_READER_H
#define AIRPORTAED_READER_H

#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>

#include "Airline.h"
#include "Airport.h"
#include "graphs/Graph.h"

using namespace std;

class Reader {
    private:
        string path;
        ifstream reader;
        unordered_map<string, int> airportCodes;
        unordered_map<string, Airline> airlineCodes;

        unordered_set<Airline> airlines;
        unordered_map<Airport, int> airports;
        Graph<Airport, list<Airline>> flights;

    public:
        // constructor
        explicit Reader(string path);

        // methods
        void readAll();
        void readAirlines();
        void readAirports();
        void readFlights();

        unordered_set<Airline> getAirlines() const;
        unordered_map<Airport, int> getAirports() const;
        Graph<Airport, list<Airline>> getFlights() const;
};


#endif //AIRPORTAED_READER_H
