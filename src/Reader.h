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

#define uMap unordered_map

class Reader {
    private:
        string path;
        ifstream reader;

        AirGraph g;

        // for search purposes
        uMap<string, Airport> airportCodes;
        uMap<string, Airport> airportNames;

    public:
        // constructor
        explicit Reader(string path);

        // methods
        void readAll();
        void readAirlines();
        void readAirports();
        void readFlights();

        AirGraph getGraph() const;
        uMap<string, Airport> getAirportCodes() const;
        uMap<string, Airport> getAirportNames() const;
};


#endif //AIRPORTAED_READER_H
