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
        uSet<string> airlineCodes;
        
        // maps used to process commands
        static map<string, int> command, target, what;
               
    public:
        // constructor
        Helpy(AirGraph& graph);

        // methods
        static void lowercase(string& s, bool uppercase = false);

        void setAirports(const uSet<string>& codes, const uMap<string, string>& names);
        void setAirlines(const uSet<string>& codes);
        void setLocations();

        string readInput(const string& instruction, uSet<string>& options);
        string readAirport();
        string readCoordinates();
        uSet<string> readUsableAirports();
        uSet<string> readUsableAirlines();
        uSet<string>* readRestrictions();

        void printPath();

        void terminal();
        void advanced_mode();
        void guided_mode();
        bool process_command(string& s1, string& s2, string& s3);

        void displayAirportInformation();
        void displayReachableAirports();
        void getShortestRoutes();
};

#endif