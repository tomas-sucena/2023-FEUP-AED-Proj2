#include "AirGraph.h"

AirGraph::AirGraph(list<Airport>* airports){
    for (Airport& a : *airports){
        nodes[a];
    }
}

void AirGraph::addFlight(string src, string dest, string airline){
    Airport& source = airportCodes[src];
    Airport& destination = airportCodes[dest];
    Airline& a = airlineCodes[airline];

    nodes[source].insert(Flight(destination, a));
}