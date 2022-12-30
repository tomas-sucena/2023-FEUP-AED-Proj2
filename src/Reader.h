#ifndef AIRPORTAED_READER_H
#define AIRPORTAED_READER_H

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "AirGraph.h"
#include "data/Airline.h"
#include "data/Airport.h"

using namespace std;

class Reader {
    private:
        string path;
        ifstream reader;

        AirGraph g;

        // for search purposes
        unordered_map<string, Airport> airportCodes;

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
        AirGraph getGraph() const;
};


#endif //AIRPORTAED_READER_H
