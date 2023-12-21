#ifndef AED2324_PRJ2_G23_AIRLINE_HPP
#define AED2324_PRJ2_G23_AIRLINE_HPP


#include <string>
#include <cstdint>

class Airline {
private:
    uint16_t code;
    std::string name;
    std::string alias;
    std::string country;

public:
    Airline(const std::string& code, const std::string& name, const std::string& alias, const std::string& country);
    std::string getCode() const;
    std::string getName() const;
    std::string getAlias() const;
    std::string getCountry() const;

    uint16_t codeToBytes(const std::string& code) const;
    std::string codeToString(uint16_t code) const;
};


#endif //AED2324_PRJ2_G23_AIRLINE_HPP
