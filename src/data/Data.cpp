#include "Data.hpp"
#include "Airline.hpp"
#include "Airport.hpp"
#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <string>
#include <iostream>

Data::Data() {
    this->searchAirportByCode = unordered_map<uint16_t, Vertex<Airport,Airline*>*>();
    this->searchAirportByName = unordered_map<std::string, Vertex<Airport,Airline*>*>();
    this->searchAirlines = unordered_map<uint16_t, Airline>();
}

void Data::loadAirport(Airport &airport) {
    auto v_ptr = flights.addVertex(airport);
    if (v_ptr == nullptr) {
        std::cout << "There is something seriously wrong with the database: airport " << airport.getName() << " is repeated multiple times" << std::endl;
        std::exit(1);
    }
    searchAirportByCode[airport.getCode()] = v_ptr;
    searchAirportByName[airport.getName()] = v_ptr;
}

void Data::loadAirline(Airline &airline) {
    searchAirlines[airline.getCode()] = airline;
}

void Data::loadFlight(uint16_t source_code, uint16_t dest_code, uint16_t airline_code) {
    Vertex<Airport,Airline*>* src = searchAirportByCode[source_code];
    Vertex<Airport,Airline*>* dst = searchAirportByCode[dest_code];
    Airline* air = &searchAirlines[airline_code];
    float distance = src->getInfo().disToOther(dst->getInfo());
    auto tmp = src->getAdj();
    tmp.push_back(Edge<Airport,Airline*>(dst, distance, air));
    src->setAdj(tmp);
}
