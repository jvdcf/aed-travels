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
    Airline(const std::string &code, const std::string &name, const std::string &alias, const std::string &country);

    Airline();

    std::string getCodeStr() const;

    uint16_t getCode() const;

    std::string getName() const;

    std::string getAlias() const;

    std::string getCountry() const;

    /**
     * @brief Transforms the 3 lettered code given as parameter in a unsigned integer of 16 bits hash.
     * @details As the code only contains 3 uppercase letters, each letter can be represented as a number from 0 to 25.\n
     * 25 in binary is 11001, so each letter can be represented by 5 bits, which gives us a total of 15 bits.\n
     * So, from the ASCII value of the letters, we subtract the ASCII value of 'A' and get the value of the letter from 0 to 25.\n
     * Now, to find the hash, we just have to put the three values together in an unsigned integer of 16 bits (leaving one bit useless).\n
     * To obtain the code from the hash, we just have to do the inverse process.
     * @note Only the hash of the code is stored in our classes
     * @param code : Airline code.
     * @return The hash of that code.
     * @note Theoretical complexity: O(1).
     */
    static uint16_t codeToHash(const std::string &code);

    /**
     * @brief Transforms the hash of the code back to the original three lettered Airline code.
     * @details Please, see the details of the method codeToHash().
     * @param code : Hash of the Airline code.
     * @return The original code as a three lettered string.
     * @note Theoretical complexity: O(1).
     */
    static std::string codeToString(uint16_t code);

};


#endif //AED2324_PRJ2_G23_AIRLINE_HPP
