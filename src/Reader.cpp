#include "Reader.h"

Reader::Reader(string path){
    if (path[path.size() - 1] != '/'){
        path += '/';
    }

    this->path = path;
}

void Reader::readAll(){
    readAirlines();
    readAirports();
    readFlights();
}

void Reader::readAirlines(){
    reader.open(path + "airlines.csv");

    string line;
    getline(reader, line);

    while (getline(reader, line)){
        istringstream line_(line);

        // read the code
        string code;
        getline(line_, code, ',');

        // read the name
        string name;
        getline(line_, name, ',');

        // read the call sign
        string callSign;
        getline(line_, callSign, ',');

        // read the country
        string country;
        getline(line_, country, '\r');

        // add the Airline to the graph
        Airline a(code, name, callSign, country);
        g.addAirline(a);
    }

    reader.close();
    reader.clear();
}

void Reader::readAirports() {
    reader.open(path + "airports.csv");

    string line;
    getline(reader, line);

    int i = 1;
    while (getline(reader, line)){
        istringstream line_(line);

        // read the code
        string code;
        getline(line_, code, ',');

        // read the name
        string name;
        getline(line_, name, ',');

        // read the call sign
        string city;
        getline(line_, city, ',');

        // read the country
        string country;
        getline(line_, country, ',');

        // read the latitude
        string lat;
        getline(line_, lat, ',');

        double latitude = stof(lat);

        // read the longitude
        string lon;
        getline(line_, lon, ',');

        double longitude = stof(lon);

        // add the Airport to the graph
        Airport a(code, name, city, country, latitude, longitude);
        g.addVertex(a);

        airportCodes[code] = a;
    }

    reader.close();
    reader.clear();
}

void Reader::readFlights() {
    reader.open(path + "flights.csv");

    string line;
    getline(reader, line);

    while (getline(reader, line)){
        istringstream line_(line);

        // read the source
        string airportA;
        getline(line_, airportA, ',');

        // read the target
        string airportB;
        getline(line_, airportB, ',');

        // read the airline
        string airline;
        getline(line_, airline, '\r');

        g.addEdge(airportA, airportB, airline);
    }

    reader.close();
    reader.clear();
}

AirGraph Reader::getGraph() const{
    return g;
}
