#ifndef AIRPORTAED_AIRLINE_H
#define AIRPORTAED_AIRLINE_H

#include <string>

using namespace std;

class Airline {
    private:
        string code;
        string name;
        string callSign;
        string country;

    public:
        // constructor
        Airline(string code, string name, string callSign, string country);

        // methods
        string getCode() const;
        string getName() const;
        string getCallSign() const;
        string getCountry() const;
};

#endif //AIRPORTAED_AIRLINE_H
