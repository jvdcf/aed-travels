#ifndef AED2324_PRJ2_G23_PARSER_HPP
#define AED2324_PRJ2_G23_PARSER_HPP


#include "data/Data.hpp"

class Parser {
private:
    /**
     * @brief Parses airport.csv and adds the Airports to the Data object.
     * @details The csv file must have the following format:\n
     *    Airport ID, Name, City, Country, Latitude, Longitude\n
     * @param data: Reference to the Data object.
     * @param csv: csv path in a string.
     */
    static void parseAirports(Data &data, const std::string &csv);

    /**
     * @brief Parses airlines.csv and adds the Airlines to the Data object.
     * @details The csv file must have the following format:\n
     *    Airline ID, Name, Callsign, Country\n
     * @param data: Reference to the Data object.
     * @param csv: csv path in a string.
     */
    static void parseAirlines(Data &data, const std::string &csv);

    /**
     * @brief Parses flights.csv and adds the edges to the graph inside the Data object.
     * @details The csv file must have the following format:\n
     *    Source Airport Code, Target Airport Code, Airline\n
     * @param data: Reference to the Data object.
     * @param csv: csv path in a string.
     */
    static void parseFlights(Data &data, const std::string &csv);

public:
    /**
     * @brief Parses the given files and returns a Data object populated.
     * @param airports: csv path in a string.
     * @param airlines: csv path in a string.
     * @param flights: csv path in a string.
     * @return Data object populated.
     * @note Theoretical complexity: O(n) where n is the number of lines in the csv files.
     */
    static Data parse(const std::string &airports, const std::string &airlines, const std::string &flights);
};


#endif //AED2324_PRJ2_G23_PARSER_HPP
