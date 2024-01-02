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

    std::unordered_set<Vertex<Airport, Airline *> *> airportFilterSet;
    std::unordered_set<Airline *> airlineFilterSet;

public:
    Data();

    // Loaders:

    /**
     * @brief Adds a new Airport to the graph.
     * @param airport
     * @note Theoretical complexity: O(V).
     */
    void loadAirport(Airport &airport);

    /**
     * @brief Adds a new Airline to the graph.
     * @param airline
     * @note Theoretical complexity: O(1).
     */
    void loadAirline(Airline &airline);

    /**
     * @brief Adds a new Flight to the graph.
     * @param source_code : Hashed Source Airport Code.
     * @param target_code : Hashed Target Airport Code.
     * @param airline_code : Hashed Airline Code.
     * @note Theoretical complexity: O(1).
     */
    void loadFlight(uint16_t source_code, uint16_t target_code, uint16_t airline_code);


    // Getters:

    const std::unordered_map<uint16_t, Vertex<Airport, Airline *> *> &getAirportsByCode() const;

    const std::unordered_map<std::string, Vertex<Airport, Airline *> *> &getAirportsByName() const;

    const std::unordered_map<uint16_t, Airline> &getAirlines() const;

    const std::unordered_set<Vertex<Airport, Airline *> *> &getAirportFilterSet() const;

    const std::unordered_set<Airline *> &getAirlineFilterSet() const;


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

    /**
     * @brief Locates the nearest airport based on the given coordinates.
     * @details Calculates the distance between the given coordinates and every airport in the graph. Then, it returns the airport with the smallest distance.
     * @param latitude : float.
     * @param longitude : float.
     * @return Vertex pointer that represents the nearest airport.
     * @note Theoretical complexity: O(V)
     */
    Vertex<Airport, Airline *> *nearestAirport(float latitude, float longitude) const;

    /**
     * @brief Finds the Airports of a given city.
     * @details Performs linear search on the vector of vertexes to find the Airports that are in the given city.
     * @param city : string.
     * @return Returns a vector of vertexes that represent the airports in the given city.
     * @note Theoretical complexity: O(V).
     */
    std::vector<Vertex<Airport, Airline *> *> searchByCity(const std::string &city) const;

    /**
     * @brief Calculates the global number of Airports, Airlines and Flights.
     * @return Returns an array of unsigned ints with the number of Airports, Airlines and Flights, respectively.
     * @note Theoretical complexity: O(V).
     */
    std::array<unsigned, 3> countAll();

    /**
     * @brief Finds the number of destinations that can be reached from a given Airport with a maximum of k stops.
     * @details Performs a BFS from the given Airport and counts the number of destinations that can be reached with a maximum of k stops.
     * @param v_ap : Source Airport.
     * @param k : unsigned int.
     * @return Returns the number of destinations that can be reached from a given Airport with a maximum of k stops.
     * @note Theoretical complexity: O(V + E).
     */
    unsigned int destinationsAtKStops(Vertex<Airport, Airline *> *v_ap, unsigned int k);

    /**
     * @brief Finds the number of flights that are operated by a given Airline.
     * @param airline_code : Hashed Airline Code.
     * @return Returns the number of flights operated by the given Airline.
     * @note Theoretical complexity: O(V).
     */
    unsigned flightsPerAirline(uint16_t airline_code);

    /**
     * @brief Finds the Airports that, if removed, areas of the network start to be unreachable.
     * @details Finds the articulation points of the graph using Tarjan's algorithm.
     * @return Returns a unordered_set of Airport Codes that are essential.
     * @note Theoretical complexity: O(V + E).
     */
    std::unordered_set<uint16_t> essentialAirports();

    /**
     * @brief Finds the nth Airport with the greatest air traffic capacity, that is, the most incoming and outgoing flights.
     * @details Copies the vector of vertexes and sorts it by the number of flights (incoming and outgoing). Then accesses the kth position.
     * @param k : number of greatest airports to find.
     * @return Returns the vertex with the kth greatest Airport.
     * @note Theoretical complexity: O(V log(V)).
     */
    Vertex<Airport, Airline *> *greatestAirport(unsigned int k);

    // returns the diameter of the graph and assigns the parameters origin ad destination to its respective values
    /**
     * @brief Finds the diameter of the graph. Adds to the vectors origin and destination the pair of vertexes that are the most distant from each other.
     * @details Does a BFS from every vertex to find the most distant vertexes from that vertex.\n
     * Then, it compares the results to find the diameter of the graph.
     * @param origin : pointer to the origin vertex.
     * @param destination : pointer to the destination vertex.
     * @return Returns the diameter of the graph.
     * @note Theoretical complexity: O(V * (V + E)).
     */
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
     * @return Returns the path as vector of Airport Codes. If a path doesn't exist, returns an empty vector.
     * @note Theoretical complexity: O(n * (V + E)) where n is the number of possible origins.
     */
    std::vector<std::string> bestFlight(const std::vector<Vertex<Airport, Airline *> *> &origins,
                                        const std::vector<Vertex<Airport, Airline *> *> &destinations) const;
};

#endif // AED2324_PRJ2_G23_DATA_HPP
