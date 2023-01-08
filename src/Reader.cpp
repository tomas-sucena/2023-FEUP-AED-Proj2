#include "Reader.h"

#include <string>

#include "AirGraph.h"
#include "Airline.h"
#include "Airport.h"

#define uMap unordered_map

/**
 * @brief creates a Reader object
 * @param path the path wherein the files to be read are
 */
Reader::Reader(string path){
    if (path[path.size() - 1] != '/'){
        path += '/';
    }

    this->path = path;
}

/**
 * @brief reads all the files
 */
void Reader::readAll(){
    readAirlines();
    readAirports();
    readFlights();
}

/**
 * @brief reads the file which contains information about the Airlines
 */
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

        airlineCodes.insert(code);
    }

    reader.close();
    reader.clear();
}

/**
 * @brief reads the file which contains information about the Airports
 */
void Reader::readAirports() {
    reader.open(path + "airports.csv");

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

        airports[code] = a;
    }

    reader.close();
    reader.clear();
}

/**
 * @brief reads the file which contains information about the flights
 */
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

/**
 * @brief creates a Helpy object, passes it the read information and returns it
 * @return a Helpy object
 */
Helpy Reader::getHelpy(){
    Helpy helpy(g);

    uSet<string> airportCodes;
    uMap<string, string> airportNames;
    uMap<string, uSet<string>> cities;
    uMap<string, uSet<string>> countries;

    for (const auto& p : airports){
        airportCodes.insert(p.first);

        string name = p.second.getName();
        airportNames.insert({name, p.first});

        string city = p.second.getCity();
        cities[city].insert(name);

        string country = p.second.getCountry();
        countries[country].insert(name);
    }

    helpy.setAirports(airportCodes, airportNames);
    helpy.setAirlines(airlineCodes);
    helpy.setLocations(cities, countries);

    return helpy;
}
