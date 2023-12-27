#ifndef AED2324_PRJ2_G23_DATA_HPP
#define AED2324_PRJ2_G23_DATA_HPP

#include "../../lib/Graph.h"
#include "Airline.hpp"
#include "Airport.hpp"
#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>

class Data {
private:
	Graph<Airport, Airline *> flights;
	std::unordered_map<uint16_t, Vertex<Airport, Airline *> *>
			searchAirportByCode;
	std::unordered_map<std::string, Vertex<Airport, Airline *> *>
			searchAirportByName;
	std::unordered_map<uint16_t, Airline> searchAirlines;

public:
	Data();

	void loadAirport(Airport &airport);

	void loadAirline(Airline &airline);

	void loadFlight(uint16_t source_code, uint16_t target_code, uint16_t airline_code);

	std::unordered_map<uint16_t, Vertex<Airport, Airline *> *> getAirportsByCode() const;

	std::unordered_map<std::string, Vertex<Airport, Airline *> *> getAirportsByName() const;

	std::unordered_map<uint16_t, Airline> getAirlines() const;

  
	std::array<unsigned, 3> countAll();
  
  unsigned flightsPerAirline(uint16_t airline_code);

	// returns the diameter of the graph and assigns the parameters origin ad destination to its respective values
	int maxTrip(std::vector<Vertex<Airport, Airline *> *> &origin, std::vector<Vertex<Airport, Airline *> *> &destination) const;
};

#endif // AED2324_PRJ2_G23_DATA_HPP
