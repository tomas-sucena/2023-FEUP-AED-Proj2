#ifndef AIRPORTAED_HELPY_H
#define AIRPORTAED_HELPY_H

#include "Airgraph.h"
#include <string>
#include <queue>
#include <map>

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

        void display_airport_information(string airport);
        //por agora meti assim, later i will change it
        void get_fastest_course();

};

#endif