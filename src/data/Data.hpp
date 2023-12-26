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
  std::unordered_map<uint16_t, Vertex<Airport, Airline *> *>
      searchAirportByCode;
  std::unordered_map<std::string, Vertex<Airport, Airline *> *>
      searchAirportByName;
  std::unordered_map<uint16_t, Airline> searchAirlines;

public:
  Data();
  void loadAirport(Airport &airport);
  void loadAirline(Airline &airline);
  void loadFlight(uint16_t source_code, uint16_t target_code,
                  uint16_t airline_code);
  std::unordered_map<uint16_t, Vertex<Airport, Airline *> *> getAirportsByCode() const;
  std::unordered_map<std::string, Vertex<Airport, Airline *> *> getAirportsByName() const;
  std::unordered_map<uint16_t, Airline> getAirlines()        const;

  std::array<unsigned, 3> countAll();
  std::vector<uint16_t> essentialAirports();

  // TODO
};

#endif // AED2324_PRJ2_G23_DATA_HPP
