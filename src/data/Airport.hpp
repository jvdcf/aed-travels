#ifndef AED2324_PRJ2_G23_AIRPORT_HPP
#define AED2324_PRJ2_G23_AIRPORT_HPP


#include <memory>
#include <string>
#include <cstdint>

class Airport {
private:
    uint16_t code;
    std::string name;
    std::string city;
    std::string country;
    float latitude;
    float longitude;

public:
    Airport(const std::string& code, const std::string& name, const std::string& city, const std::string& country, float latitude, float longitude);
    std::string getCodeStr() const;
    uint16_t    getCode() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;
    float distanceTo(float pLat, float pLon) const;
    static uint16_t codeToHash(const std::string& code);
    static std::string codeToString(uint16_t code);
    bool operator==(const Airport& other); 
};

#endif //AED2324_PRJ2_G23_AIRPORT_HPP
