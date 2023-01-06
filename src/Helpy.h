#ifndef AIRPORTAED_HELPY_H
#define AIRPORTAED_HELPY_H

#include <map>
#include <string>

#include "data/Airport.h"
#include "AirGraph.h"

#define uMap unordered_map
#define uSet unordered_set

class Helpy {
    private:
        AirGraph graph;

        // for search purposes
        uSet<string> airportCodes;
        uMap<string, string> airportNames;
        
        // maps used to process commands
        static map<string, int> command, target, what;
               
    public:
        // constructor
        Helpy(AirGraph& airGraph, const uMap<string, Airport>& airports);

        // methods
        string readInput(string& instruction, uSet<string>& options);
        string readAirport();

        void terminal();
        void advanced_mode();
        void guided_mode();
        bool process_command(string& s1, string& s2, string& s3);

        void displayAirportInformation();
        void displayReachableAirports(string& start, int flights);
        void getShortestRoutes();
};

#endif