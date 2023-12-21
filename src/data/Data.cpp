#include "Data.hpp"
#include "Airline.hpp"
#include "Airport.hpp"
#include <cstdint>

Data::Data() {
    // TODO
}

void Data::loadAirport(Airport &airport) {
    flights.addVertex(airport);
    searchAirportByCode[airport.getCode()] = flights.findVertex(airport);
    searchAirportByName[airport.getName()] = flights.findVertex(airport);
}

void Data::loadAirline(Airline &airline) {
    searchAirlines[airline.getCode()] = airline;
}

void Data::loadFlight(uint16_t source_code, uint16_t dest_code, uint16_t airline_code) {
    Vertex<Airport,Airline>* src = searchAirportByCode[source_code];
    Vertex<Airport,Airline>* dst = searchAirportByCode[dest_code];
    Airline air = searchAirlines[airline_code];
    // TODO: distance
    float distance = 0;
    auto tmp = src->getAdj();
    tmp.push_back(Edge<Airport,Airline>(dst, distance, air));
    src->setAdj(tmp);
}
