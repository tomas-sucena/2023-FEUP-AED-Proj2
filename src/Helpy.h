#ifndef AIRPORTAED_HELPY_H
#define AIRPORTAED_HELPY_H

#include <map>
#include <string>
#include <queue>
#include <map>

#include "Airgraph.h"


class Helpy {
    private:
        AirGraph graph;
        
        // mapas usados para processar comandos
        static map<string, int> command, target, what;
               
    public:
        // constructor
        Helpy(AirGraph airGraph);

        // methods
        void terminal();
        void advanced_mode();
        void guided_mode();
        bool process_command(string& s1, string& s2, string& s3);

        void displayAirportInformation(string airport);
        void getShortestRoute() const;

};

#endif