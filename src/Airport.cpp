#include "Airport.h"

/**
 * @brief Construct a new Airport:: Airport object
 */
Airport::Airport() {}

/**
 * @brief Construct a new Airport:: Airport object
 * @param code code of the Airport
 * @param name name of the Airport
 * @param city city of the Airport
 * @param country country of the Airport
 * @param latitude latitude of the Airport
 * @param longitude longitude of the Airport
 */
Airport::Airport(string& code, string& name, string& city, string& country, double latitude, double longitude) :
    code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {}

/**
 * @brief Copy constructor of Airport
 * @param a Airport whose values will be copied
 */
Airport::Airport(const Airport &a) :
    code(a.getCode()), name(a.getName()), city(a.getCity()), country(a.getCountry()),
    latitude(a.getLat()), longitude(a.getLong()) {}

/**
 * @brief returns the code of the Airport
 * @return code of the Airport
 */
string Airport::getCode() const{
    return code;
}

/**
 * @brief returns the name of the Airport
 * @return name of the Airport
 */
string Airport::getName() const{
    return name;
}

/**
 * @brief returns the city of the Airport
 * @return city of the Airport
 */
string Airport::getCity() const{
    return city;
}

/**
 * @brief returns the country of the Airport
 * @return country of the Airport
 */
string Airport::getCountry() const{
    return country;
}

/**
 * @brief returns the latitude of the Airport
 * @return latitude of the Airport
 */
double Airport::getLat() const{
    return latitude;
}

/**
 * @brief returns the longitude of the Airport
 * @return longitude of the Airport
 */
double Airport::getLong() const{
    return longitude;
}

/**
 * @brief calculates the distance between the Airport and the location defined by the pair (lat, lon)
 * @complexity O(1)
 * @param lat latitude
 * @param lon longitude
 * @return calculated distance
 */
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

/**
 * @brief calculates the distance between two Airports
 * @complexity O(1)
 * @param a second Airport
 * @return calculated distance
 */
double Airport::getDistance(const Airport &a) const{
    return getDistance(a.getLat(), a.getLong());
}

/**
 * @brief compares two Airports and verifies if they are the same
 * @complexity O(1)
 * @param a right side of the comparison operation
 * @return 'true' if the Airports are equal, 'false' otherwise
 */
bool Airport::operator==(const Airport& a) const{
    return (code == a.getCode());
}