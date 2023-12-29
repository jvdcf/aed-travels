#ifndef AED2324_PRJ2_G23_RUNTIME_HPP
#define AED2324_PRJ2_G23_RUNTIME_HPP

#include "data/Data.hpp"
#include <vector>

class Runtime {
private:
    Data *data;

    void processArgs(std::vector<std::string> args);

    void countAll();

    void displayAirport(Vertex<Airport, Airline *> *v_ap, bool full, unsigned k);

    void displayAirline(Airline &al);

    void displayCity(const std::string &city);

    void essentialAirports();

    void greatestAirport(int k);

    /**
     * @brief Finds the flights with the least number of stops between a set of origins and a set of destinations (see the method with the same name in Data).
     * @details Creates a vector with all the possible origins and another with all the possible destinations and performs and executes the method bestFlight() of the class Data with those arguments.\n
     * If the argument is an Airport code, the vector will contain just that airport.\n
     * If the argument is a location, the vector will contain the nearest Airport.\n
     * If the argument is a City name, the vector will contain all the Airports in that City.
     * @param args : vector of arguments.
     * @note Theoretical complexity: O(n * (V + E)) where n is the number of possible origins.
     */
    void bestFlight(std::vector<std::string> args);

    /**
     * @brief Adds the Airports and the Airlines in the arguments to the filter.
     * @param args : vector of arguments.
     * @note Theoretical complexity: O(1).
     */
    void addFilters(std::vector<std::string> args);

    /**
     * @brief Displays all the filters.
     * @note Theoretical complexity: O(n) where n is the number of filters added.
     */
    void displayFilters();

    void maxTrip();

public:
    explicit Runtime(Data *data);

    [[noreturn]] void run();
};

#endif // AED2324_PRJ2_G23_RUNTIME_HPP
