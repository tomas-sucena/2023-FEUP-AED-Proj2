#include "Airline.h"

/**
 * @brief Construct a new Airline:: Airline object
 * 
 */
Airline::Airline() {}

/**
 * @brief Construct a new Airline:: Airline object
 * 
 * @param code 
 * @param name 
 * @param callSign 
 * @param country 
 */
Airline::Airline(string code, string name, string callSign, string country) :
    code(code), name(name), callSign(callSign), country(country) {}

/**
 * @brief Construct a new Airline:: Airline object
 * 
 * @param a 
 */
Airline::Airline(const Airline& a) :
    code(a.getCode()), name(a.getName()), callSign(a.getCallSign()), country(a.getCountry()) {}

/**
 * @brief 
 * 
 * @return string 
 */
string Airline::getCode() const{
    return code;
}

/**
 * @brief 
 * 
 * @return string 
 */
string Airline::getName() const{
    return name;
}

/**
 * @brief 
 * 
 * @return string 
 */
string Airline::getCallSign() const{
    return callSign;
}

/**
 * @brief 
 * 
 * @return string 
 */
string Airline::getCountry() const{
    return country;
}

/**
 * @brief 
 * 
 * @param a 
 * @return true 
 * @return false 
 */
bool Airline::operator==(const Airline &a) const{
    return (code == a.getCode());
}