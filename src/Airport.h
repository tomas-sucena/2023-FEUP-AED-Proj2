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
        Airport();
        Airport(string& code, string& name, string& city, string& country, double latitude, double longitude);
        Airport(const Airport& a);

        // methods
        string getCode() const;
        string getName() const;
        string getCity() const;
        string getCountry() const;
        double getLat() const;
        double getLong() const;

        double getDistance(double lat2, double long2) const;
        double getDistance(const Airport& a) const;

        bool operator==(const Airport& a) const;
};

namespace std {
    template <>
    struct hash<Airport> {
        size_t operator()(const Airport& a) const{
            return hash<string>()(a.getCode());
        }
    };
}

#endif //AIRPORTAED_AIRPORT_H
