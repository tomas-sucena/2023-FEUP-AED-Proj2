#ifndef AIRPORTAED_READER_H
#define AIRPORTAED_READER_H

#include <iostream>

#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Reader {
    private:
        ifstream airlines;
        ifstream airports;
        ifstream flights;

    public:
        // constructor
        Reader(string path);

        // methods
        void read();
};


#endif //AIRPORTAED_READER_H
