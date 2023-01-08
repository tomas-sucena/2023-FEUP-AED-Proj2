#ifndef AIRPORTAED_READER_H
#define AIRPORTAED_READER_H

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "AirGraph.h"
#include "Airline.h"
#include "Airport.h"
#include "Helpy.h"

using namespace std;

#define uMap unordered_map
#define uSet unordered_set

class Reader {
    private:
        string path;
        ifstream reader;

        AirGraph g;

        // for search purposes
        uMap<string, Airport> airports;
        uSet<string> airlineCodes;

    public:
        // constructor
        explicit Reader(string path);

        // methods
        void readAll();
        void readAirlines();
        void readAirports();
        void readFlights();

        Helpy getHelpy();
};


#endif //AIRPORTAED_READER_H
