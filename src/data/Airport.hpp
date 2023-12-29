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
    Airport(const std::string &code, const std::string &name, const std::string &city, const std::string &country,
            float latitude, float longitude);

    std::string getCodeStr() const;

    uint16_t getCode() const;

    std::string getName() const;

    std::string getCity() const;

    std::string getCountry() const;

    float getLatitude() const;

    float getLongitude() const;

    /**
     * @brief Calculates the distance from the Airport to the point whose coordinates are given in the parameters.
     * @details Calculates the distance using the Haversine Distance Function.
     * @param pLat : latitude.
     * @param pLon : longitude.
     * @return Returns the distance to that point.
     * @note Theoretical complexity: O(1).
     */
    float distanceTo(float pLat, float pLon) const;

    /**
     * @brief Transforms the 3 lettered code given as parameter in a unsigned integer of 16 bits hash.
     * @details As the code only contains 3 uppercase letters, each letter can be represented as a number from 0 to 25.\n
     * 25 in binary is 11001, so each letter can be represented by 5 bits, which gives us a total of 15 bits.\n
     * So, from the ASCII value of the letters, we subtract the ASCII value of 'A' and get the value of the letter from 0 to 25.\n
     * Now, to find the hash, we just have to put the three values together in an unsigned integer of 16 bits (leaving one bit useless).\n
     * To obtain the code from the hash, we just have to do the inverse process.
     * @note Only the hash of the code is stored in our classes
     * @param code : Airport code.
     * @return The hash of that code.
     * @note Theoretical complexity: O(1).
     */
    static uint16_t codeToHash(const std::string &code);

    /**
     * @brief Transforms the hash of the code back to the original three lettered Airport code.
     * @details Please, see the details of the method codeToHash().
     * @param code : Hash of the Airport code.
     * @return The original code as a three lettered string.
     * @note Theoretical complexity: O(1).
     */
    static std::string codeToString(uint16_t code);

    bool operator==(const Airport &other) const;
};

#endif //AED2324_PRJ2_G23_AIRPORT_HPP
