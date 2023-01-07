#include "Airport.h"

Airport::Airport() {}

Airport::Airport(string code, string name, string city, string country, double latitude, double longitude) :
    code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {}

Airport::Airport(const Airport &a) :
    code(a.getCode()), name(a.getName()), city(a.getCity()), country(a.getCountry()),
    latitude(a.getLat()), longitude(a.getLong()) {}

string Airport::getCode() const{
    return code;
}

string Airport::getName() const{
    return name;
}

string Airport::getCity() const{
    return city;
}

string Airport::getCountry() const{
    return country;
}

double Airport::getLat() const{
    return latitude;
}

double Airport::getLong() const{
    return longitude;
}

double Airport::getDistance(double lat, double lon) const{
    double latA = latitude, lonA = longitude;

    double dLat = (lat - latA);
    double dLong = (lon - lonA);

    // convert to radians
    latA *= M_PI / 180;
    lat *= M_PI / 180;
    dLat *= M_PI / 180;
    dLong *= M_PI / 180;

    // apply formula
    double haver = pow(sin(dLat / 2), 2) + pow(sin(dLong / 2), 2) *
                   cos(latA) * cos(lat);
    double sine = 2 * asin(sqrt(haver));

    return 6371 * sine; // 6371 -> Earth's radius
}

double Airport::getDistance(const Airport &a) const{
    return getDistance(a.getLat(), a.getLong());
}

bool Airport::operator==(const Airport& a) const{
    return (code == a.getCode());
}
