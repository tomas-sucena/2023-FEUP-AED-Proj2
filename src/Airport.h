#ifndef AIRPORTAED_AIRPORT_H
#define AIRPORTAED_AIRPORT_H

#include <cmath>

#include <string>

using namespace std;

class Airport {
    private:
        string code;
        string name;
        string city;
        string country;
        double latitude, longitude;

    public:
        // constructor
        Airport(string code, string name, string city, string country, double latitude, double longitude);

        // methods
        string getCode() const;
        string getName() const;
        string getCity() const;
        string getCountry() const;
        double getLat() const;
        double getLong() const;

        double getDistance(const Airport& a) const;
};

#endif //AIRPORTAED_AIRPORT_H
