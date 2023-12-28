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
	 * @param code
	 * @return true if the code is valid and false if it isn't.
	 */
	bool addAirportToFilter(const std::string& code);

	/**
	 * Attempts to add an airline to the filter set. If successful returns true and false otherwise.
	 * @param code
	 * @return true if the code is valid and false if it isn't.
	 */
	bool addAirlineToFilter(const std::string &code);

	/**
	 * Clears all the filters that were added.
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

    std::vector<Vertex<Airport, Airline *> *>
    shortestPath(Vertex<Airport, Airline *> *origin, std::vector<Vertex<Airport, Airline *> *> destinations) const;

    std::vector<std::string> bestFlight(const std::vector<Vertex<Airport, Airline *> *> &origins,
                                        const std::vector<Vertex<Airport, Airline *> *> &destinations) const;
};

#endif // AED2324_PRJ2_G23_DATA_HPP
