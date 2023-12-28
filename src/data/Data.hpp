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

	void calculateIncomingFlights();

public:
	Data();

	void loadAirport(Airport &airport);

	void loadAirline(Airline &airline);

	void loadFlight(uint16_t source_code, uint16_t target_code, uint16_t airline_code);

	std::unordered_map<uint16_t, Vertex<Airport, Airline *> *> getAirportsByCode() const;

	std::unordered_map<std::string, Vertex<Airport, Airline *> *> getAirportsByName() const;

	std::unordered_map<uint16_t, Airline> getAirlines() const;

	std::vector<Vertex<Airport, Airline *> *> searchByCity(std::string city) const;

	Vertex<Airport, Airline *> * nearestAirport(float latitude, float longitude) const;
  
  
	std::array<unsigned, 3> countAll();
  
  unsigned flightsPerAirline(uint16_t airline_code);
  
  std::unordered_set<uint16_t> essentialAirports();
  
  Vertex<Airport, Airline *> *greatestAirport(unsigned int k);

	// returns the diameter of the graph and assigns the parameters origin ad destination to its respective values
	int maxTrip(std::vector<Vertex<Airport, Airline *> *> &origin, std::vector<Vertex<Airport, Airline *> *> &destination) const;
 
  std::vector<Vertex<Airport, Airline *> *>
	shortestPath(Vertex<Airport, Airline *> *origin, std::vector<Vertex<Airport, Airline *> *> destinations) const;

	std::vector<std::string> bestFlight(const std::vector<Vertex<Airport, Airline *> *> &origins,
										const std::vector<Vertex<Airport, Airline *> *> &destinations) const;
};

#endif // AED2324_PRJ2_G23_DATA_HPP
