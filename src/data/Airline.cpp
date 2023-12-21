#include "Airline.hpp"
#include <cmath>
#include <cstdint>

Airline::Airline(const std::string& code, const std::string& name, const std::string& alias, const std::string& country) {
    this->code = codeToHash(code);
    this->name = name;
    this->alias = alias;
    this->country = country;
}
Airline::Airline() {
    this->code = 0;
    this->name = nullptr;
    this->alias = nullptr;
    this->country = nullptr;
}

std::string Airline::getCodeStr() const {
    return codeToString(this->code);
}

uint16_t Airline::getCode() const {
    return this->code;
}

std::string Airline::getName() const {
    return this->name;
}

std::string Airline::getAlias() const {
    return this->alias;
}

std::string Airline::getCountry() const {
    return this->country;
}

uint16_t Airline::codeToHash(const std::string& code) {
    uint16_t res = 0;
    for (int i = 2; i >= 0; --i) {
        res <<= 5;
        res += (code[i] - 'A') & (32-1); // "& (32-1)": obtain the 5 Least Significant Bits. (32-1) = 31 = 0b11111
    }
    return res;
}
    
std::string Airline::codeToString(uint16_t code) {
    std::string res;
    for (int i = 0; i < 3; ++i) { 
        res.push_back((code & (32-1)) + 'A'); // "& (32-1)": obtain the 5 Least Significant Bits. (32-1) = 31 = 0b11111
        code >>= 5;
    }
    return res;
}

