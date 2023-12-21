#ifndef AED2324_PRJ2_G23_DATA_HPP
#define AED2324_PRJ2_G23_DATA_HPP


#include <unordered_set>
#include <unordered_map>
#include "Airport.hpp"
#include "Airline.hpp"
#include "../../lib/Graph.h"

class Data {
private:
    Graph<Airport> flights;
    std::unordered_map<uint16_t, Vertex<Airport>*> tabVertex;
    std::unordered_map<uint16_t, Airline> tabAirlines;

public:
    Data();
    void loadAirport(Airport& airport);
    void loadAirline(Airline& airline);
    void loadFlight(Airport& source, Airport& target, Airline& airline);

    // TODO
};


#endif //AED2324_PRJ2_G23_DATA_HPP
