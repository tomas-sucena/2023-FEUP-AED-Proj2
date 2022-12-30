#include "Airline.h"

Airline::Airline() {}

Airline::Airline(string code, string name, string callSign, string country) :
    code(code), name(name), callSign(callSign), country(country) {}

Airline::Airline(const Airline& a) :
    code(a.getCode()), name(a.getName()), callSign(a.getCallSign()), country(a.getCountry()) {}

string Airline::getCode() const{
    return code;
}

string Airline::getName() const{
    return name;
}

string Airline::getCallSign() const{
    return callSign;
}

string Airline::getCountry() const{
    return country;
}

bool Airline::operator==(const Airline &a) const{
    return (code == a.getCode());
}

