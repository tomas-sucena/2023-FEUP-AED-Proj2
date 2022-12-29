#include "Airport.h"

Airport::Airport(string code, string name, string city, string country, double latitude, double longitude) :
    code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {}

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

double Airport::getDistance(const Airport &a) const{
    double lat1 = latitude, lat2 = a.getLat(),
           long1 = longitude, long2 = a.getLong();

    double dLat = (lat2 - lat1);
    double dLong = (long2 - long1);

    // convert to radians
    lat1 *= M_PI / 180;
    lat2 *= M_PI / 180;
    dLat *= M_PI / 180;
    dLong *= M_PI / 180;

    // apply formula
    double haver = pow(sin(dLat / 2), 2) + pow(sin(dLong / 2), 2) *
                   cos(lat1) * cos(lat2);
    double sine = 2 * asin(sqrt(haver));

    return 6371 * sine; // 6371 -> Earth's radius
}

bool Airport::operator==(const Airport& a) const{
    return (code == a.getCode());
}
