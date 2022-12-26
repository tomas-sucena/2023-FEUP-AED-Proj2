#include "Reader.h"

Reader::Reader(string path){
    airlines.open(path + "airlines.csv");
    airports.open(path + "airports.csv");
    flights.open(path + "flights.csv");
}

void Reader::read(){
    // TESTE
    string temp;
    getline(airlines, temp);

    cout << temp << endl;
}
