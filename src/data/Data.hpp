#ifndef AED2324_PRJ2_G23_DATA_HPP
#define AED2324_PRJ2_G23_DATA_HPP

#include <cstdint>
#include <string>
#include <unordered_map>
#include "Airport.hpp"
#include "Airline.hpp"
#include "../../lib/Graph.h"

class Data {
private:
    Graph<Airport, Airline*> flights;
    std::unordered_map<uint16_t, Vertex<Airport, Airline*>*> searchAirportByCode;
    std::unordered_map<std::string, Vertex<Airport, Airline*>*> searchAirportByName;
    std::unordered_map<uint16_t, Airline> searchAirlines;

public:
    Data();
    void loadAirport(Airport& airport);
    void loadAirline(Airline& airline);
    void loadFlight(uint16_t source_code, uint16_t target_code, uint16_t airline_code);

    // TODO
};


#endif //AED2324_PRJ2_G23_DATA_HPP
