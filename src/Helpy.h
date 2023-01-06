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
        uMap<string, Airport> airportCodes;
        uMap<string, Airport> airportNames;
        
        // mapas usados para processar comandos
        static map<string, int> command, target, what;
               
    public:
        // constructor
        Helpy(AirGraph& airGraph);

        // methods
        void setAirports(uMap<string, Airport>& codes, uMap<string, Airport>& names);

        string readInput(string& instruction, uSet<string>& options);

        void terminal();
        void advanced_mode();
        void guided_mode();
        bool process_command(string& s1, string& s2, string& s3);

        string readAirport();

        void displayAirportInformation(string& airport);
        void displayReachableAirports(string& start, int flights);
        void getShortestRoutes();
};

#endif