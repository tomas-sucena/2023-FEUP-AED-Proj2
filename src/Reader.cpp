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

        // create the Airline
        Airline a(code, name, callSign, country);

        airlines.insert(a);
        //airlineCodes[code] = a;
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

        // create the airport
        Airport a(code, name, city, country, latitude, longitude);

        flights.addNode(a);
        airports[a] = airportCodes[code] = i++;
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
        string temp;
        getline(line_, temp, ',');

        int src = airportCodes[temp];

        // read the target
        getline(line_, temp, ',');

        int target = airportCodes[temp];

        // read the airline


    }

    reader.close();
    reader.clear();
}

unordered_set<Airline> Reader::getAirlines() const{
    return airlines;
}

unordered_map<Airport, int> Reader::getAirports() const{
    return airports;
}

Graph<Airport, list<Airline>> Reader::getFlights() const{
    return flights;
}
