#ifndef AED2324_PRJ2_G23_DATA_HPP
#define AED2324_PRJ2_G23_DATA_HPP

#include "../../lib/Graph.h"
#include "Airline.hpp"
#include "Airport.hpp"
#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Data {
private:
    Graph<Airport, Airline *> flights;
    std::unordered_map<uint16_t, Vertex<Airport, Airline *> *> searchAirportByCode;
    std::unordered_map<std::string, Vertex<Airport, Airline *> *> searchAirportByName;
    std::unordered_map<uint16_t, Airline> searchAirlines;

    std::vector<Vertex<Airport, Airline *> *> airportFilterSet;
    std::vector<Airline *> airlineFilterSet;

public:
    Data();

    // Loaders:

    void loadAirport(Airport &airport);

    void loadAirline(Airline &airline);

    void loadFlight(uint16_t source_code, uint16_t target_code, uint16_t airline_code);


    // Getters:

    const std::unordered_map<uint16_t, Vertex<Airport, Airline *> *> &getAirportsByCode() const;

    const std::unordered_map<std::string, Vertex<Airport, Airline *> *> &getAirportsByName() const;

    const std::unordered_map<uint16_t, Airline> &getAirlines() const;

    const vector<Vertex<Airport, Airline *> *> &getAirportFilterSet() const;

    const vector<Airline *> &getAirlineFilterSet() const;


    // Methods:

    /**
     * Attempts to add a airport to the filter set. If successful returns true and false otherwise.
     * @param code of the Airport.
     * @return true if the code is valid and false if it isn't.
     * @note Theoretical complexity: O(1).
     */
    bool addAirportToFilter(const std::string &code);

    /**
     * Attempts to add an airline to the filter set. If successful returns true and false otherwise.
     * @param code of the Airline.
     * @return true if the code is valid and false if it isn't.
     * @note Theoretical complexity: O(1).
     */
    bool addAirlineToFilter(const std::string &code);

    /**
     * Clears all the filters that were added.
     * @note Theoretical complexity: O(n) where n is the number of filters.
     */
    void clearFilters();

    Vertex<Airport, Airline *> *nearestAirport(float latitude, float longitude) const;

    std::vector<Vertex<Airport, Airline *> *> searchByCity(const std::string &city) const;

    std::array<unsigned, 3> countAll();

    unsigned int destinationsAtKStops(Vertex<Airport, Airline *> *v_ap, unsigned int k);

    unsigned flightsPerAirline(uint16_t airline_code);

    std::unordered_set<uint16_t> essentialAirports();

    Vertex<Airport, Airline *> *greatestAirport(unsigned int k);

    // returns the diameter of the graph and assigns the parameters origin ad destination to its respective values
    int maxTrip(std::vector<Vertex<Airport, Airline *> *> &origin,
                std::vector<Vertex<Airport, Airline *> *> &destination) const;

    /**
     * @brief Finds the shortest path between a origin and a set of possible destinations. Returns a vector with the path.
     * @details Performs a BFS to find the shortest path from the vertex origin to the vertex destination (or destinations in case there is more than one targeted destination).\n
     * It takes account of what is on the filters, only showing flights that are operated by those Airlines and that do not pass through any of those Airports.
     * @param origin : pointer to the origin vertex.
     * @param destinations : vector of vertex pointers of targeted destinations.
     * @return Returns a vector of vertexes in order of traverse (from the origin to one of the destinations) - aka path. If a path doesn't exist, returns an empty vector.
     * @note Theoretical complexity: O(V + E).
     */
    std::vector<Vertex<Airport, Airline *> *>
    shortestPath(Vertex<Airport, Airline *> *origin, std::vector<Vertex<Airport, Airline *> *> destinations) const;

    /**
     * @brief Finds the flights with the least number of stops between a set of origins and a set of destinations.
     * @details For every possible origin, performs the shortest path algorithm (see method shortestPath()).
     * @param origins : vector of vertex pointers of possible origins.
     * @param destinations : vector of vertex pointers of targeted destinations.
     * @return Returns the path as vector of Airport Codes.
     * @note Theoretical complexity: O(n * (V + E)) where n is the number of possible origins.
     */
    std::vector<std::string> bestFlight(const std::vector<Vertex<Airport, Airline *> *> &origins,
                                        const std::vector<Vertex<Airport, Airline *> *> &destinations) const;
};

#endif // AED2324_PRJ2_G23_DATA_HPP
