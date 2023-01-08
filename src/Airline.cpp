#include "Airline.h"

/**
 * @brief Default constructor of Airline
 */
Airline::Airline() {}

/**
 * @brief Construct a new Airline:: Airline object
 * @param code code of the Airline
 * @param name name of the Airline
 * @param callSign call sign of the Airline
 * @param country country of the Airline
 */
Airline::Airline(const string& code, const string& name, const string& callSign, const string& country) :
    code(code), name(name), callSign(callSign), country(country) {}

/**
 * @brief Copy constructor of Airline
 * @param a Airline whose values will be copied
 */
Airline::Airline(const Airline& a) :
    code(a.getCode()), name(a.getName()), callSign(a.getCallSign()), country(a.getCountry()) {}

/**
 * @brief returns the code of the Airline
 * @return code of the Airline
 */
string Airline::getCode() const{
    return code;
}

/**
 * @brief returns the name of the Airline
 * @return name of the Airline
 */
string Airline::getName() const{
    return name;
}

/**
 * @brief returns the call sign of the Airline
 * @return call sign of the Airline
 */
string Airline::getCallSign() const{
    return callSign;
}

/**
 * @brief returns the country of the Airline
 * @return country of the Airline
 */
string Airline::getCountry() const{
    return country;
}

/**
 * @brief compares two Airports and verifies if they are the same
 * @complexity O(1)
 * @param a right side of the comparison operation
 * @return 'true' if the Airlines are equal, 'false' otherwise
 */
bool Airline::operator==(const Airline &a) const{
    return (code == a.getCode());
}