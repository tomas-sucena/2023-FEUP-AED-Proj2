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
        // constructors
        Airline();
        Airline(const string& code, const string& name, const string& callSign, const string& country);
        Airline(const Airline& a);

        // methods
        string getCode() const;
        string getName() const;
        string getCallSign() const;
        string getCountry() const;

        bool operator==(const Airline& a) const;
};

namespace std {
    template <>
    struct hash<Airline> {
        size_t operator()(const Airline& a) const{
            return hash<string>()(a.getCode());
        }
    };
}

#endif //AIRPORTAED_AIRLINE_H
