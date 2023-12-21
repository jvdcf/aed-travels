#include "Airport.hpp"
#include "Data.hpp"
#include <cstdint>

Airport::Airport(const std::string& code, const std::string& name, const std::string& city, const std::string& country,
                 float latitude, float longitude) {
    this->code      = codeToHash(code);
    this->name      = name;
    this->city      = city;
    this->country   = country;
    this->latitude  = latitude;
    this->longitude = longitude;

}

std::string Airport::getCodeStr() const {
    return codeToString(this->code);
}

uint16_t Airport::getCode() const {
    return code;
}

std::string Airport::getName() const {
    return name;
}

std::string Airport::getCity() const {
    return city;
}

std::string Airport::getCountry() const {
    return country;
}

float Airport::getLatitude() const {
    return latitude;
}

float Airport::getLongitude() const {
    return longitude;
}

uint16_t Airport::codeToHash(const std::string& code) const {
    uint16_t res = 0;
    for (int i = 2; i >= 0; --i) {
        res <<= 5;
        res += (code[i] - 'A') & (32-1); // "& (32-1)": obtain the 5 Least Significant Bits. (32-1) = 31 = 0b11111
    }
    return res;
}
    
std::string Airport::codeToString(uint16_t code) const {
    std::string res;
    for (int i = 0; i < 3; ++i) { 
        res.push_back((code & (32-1)) + 'A'); // "& (32-1)": obtain the 5 Least Significant Bits. (32-1) = 31 = 0b11111
        code >>= 5;
    }
    return res;
}

