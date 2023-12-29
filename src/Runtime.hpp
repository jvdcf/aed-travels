#ifndef AED2324_PRJ2_G23_RUNTIME_HPP
#define AED2324_PRJ2_G23_RUNTIME_HPP

#include "data/Data.hpp"
#include <vector>

class Runtime {
private:
    Data *data;

    /**
     * @brief reads the user commands and creates a process to be executed.
     * @param args
     */
    void processArgs(std::vector<std::string> args);

    /**
     * @brief list_counts command
     * @details Counts the number of Airports, Airlines and Flights in Data.\n
     * See Data::countAll().
     * @note Theoretical complexity: O(V)
     */
    void countAll();

    /**
     * @brief display_airport command
     * @details Displays information about an airport, optionally displaying all flight information.
     * @param v_ap: Vertex of the Airport to be displayed.
     * @param full: If true, displays all flight information.
     * @param k: The maximum number of stops for the count of different destinations.
     * @note Theoretical complexity: O(V + E)
     */
    void displayAirport(Vertex<Airport, Airline *> *v_ap, bool full, unsigned k);

    /**
     * @brief display_airline command
     * @details Displays information about an airline and their number of flights.
     * @param al: Airline to be displayed.
     * @note Theoretical complexity: O(V)
     */
    void displayAirline(Airline &al);

    /**
     * @brief display_city command
     * @details Displays information about a city.
     * @param city: City to be displayed.
     * @note Theoretical complexity: O(V)
     */
    void displayCity(const std::string &city);

    /**
     * @brief essential_airport command
     * @details Displays all essential airports codes to the network's circulation capability.\n
     * See Data::essentialAirports().
     * @note Theoretical complexity: O(V * (V + E))
     */
    void essentialAirports();

    /**
     * @brief greatest_airport command
     * @details Displays the k-th airport with the most incoming and outgoing flights.\n
     * See Data::greatestAirport().
     * @param k: The k-th airport.
     * @note Theoretical complexity: O(V log(V))
     */
    void greatestAirport(int k);

    /**
     * @brief Finds the flights with the least number of stops between a set of origins and a set of destinations (see Data::bestFlight()).
     * @details Creates a vector with all the possible origins and another with all the possible destinations and performs and executes the method Data::bestFlight() with those arguments.\n
     * If the argument is an Airport code, the vector will contain just that airport.\n
     * If the argument is a location, the vector will contain the nearest Airport.\n
     * If the argument is a City name, the vector will contain all the Airports in that City.
     * @param args : vector of arguments.
     * @note Theoretical complexity: O(n * (V + E)) where n is the number of possible origins.
     */
    void bestFlight(std::vector<std::string> args);

    /**
     * @brief Adds the Airports and the Airlines in the arguments to the filter.
     * @details See Data::addAirportToFilter() and Data::addAirlineToFilter().
     * @param args : vector of arguments.
     * @note Theoretical complexity: O(1).
     */
    void addFilters(std::vector<std::string> args);

    /**
     * @brief Displays all the filters.
     * @note Theoretical complexity: O(n) where n is the number of filters added.
     */
    void displayFilters();

    /**
     * @brief max_trip command
     * @details Displays the flight trip(s) with the greatest number of stops.\n
     * See Data::maxTrip().
     * @note Theoretical complexity: O(V * (V + E))
     */
    void maxTrip();

public:
    explicit Runtime(Data *data);

    [[noreturn]] void run();
};

#endif // AED2324_PRJ2_G23_RUNTIME_HPP
