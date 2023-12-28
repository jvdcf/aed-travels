#ifndef AED2324_PRJ2_G23_PARSER_HPP
#define AED2324_PRJ2_G23_PARSER_HPP


#include "data/Data.hpp"

class Parser {
private:
    static void parseAirports(Data &data, const std::string &csv);

    static void parseAirlines(Data &data, const std::string &csv);

    static void parseFlights(Data &data, const std::string &csv);

public:
    static Data parse(const std::string &airports, const std::string &airlines, const std::string &flights);
};


#endif //AED2324_PRJ2_G23_PARSER_HPP
