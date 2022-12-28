#include "Reader.h"

Reader::Reader(string path){
    if (path[path.size() - 1] != '/'){
        path += '/';
    }

    airlines.open(path + "airlines.csv");
    airports.open(path + "airports.csv");
    flights.open(path + "flights.csv");
}

void Reader::read(){
    // TESTE
    string line;
    getline(airlines, line);

    while (getline(airlines, line)){
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
    }

}
