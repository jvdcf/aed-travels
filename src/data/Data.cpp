#include "Data.hpp"
#include "Airline.hpp"
#include "Airport.hpp"
#include <cstdint>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>

Data::Data() {
    this->searchAirportByCode = unordered_map<uint16_t, Vertex<Airport,Airline*>*>();
    this->searchAirportByName = unordered_map<std::string, Vertex<Airport,Airline*>*>();
    this->searchAirlines = unordered_map<uint16_t, Airline>();
}

void Data::loadAirport(Airport &airport) {
    auto v_ptr = flights.addVertex(airport);
    if (v_ptr == nullptr) {
        std::cerr << "ERROR   : There is something seriously wrong with the database: airport " << airport.getName() << " is repeated multiple times" << std::endl;
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

std::unordered_map<uint16_t, Vertex<Airport, Airline *> *> Data::getAirportsByCode() const {
  return searchAirportByCode;
}
std::unordered_map<std::string, Vertex<Airport, Airline *> *> Data::getAirportsByName() const {
  return searchAirportByName;
}
std::unordered_map<uint16_t, Airline> Data::getAirlines() const {
  return searchAirlines;
}




// ========================================================================================

std::array<unsigned, 3> Data::countAll() {
  unsigned airportsCount = searchAirportByCode.size();
  unsigned airlinesCount = searchAirlines.size();
  unsigned flightsCount = 0;
  for (auto v: flights.getVertexSet()) {
    flightsCount += v->getAdj().size();
  }

  return {airportsCount, airlinesCount, flightsCount};
}

std::vector<Vertex<Airport, Airline *> *>
Data::shortestPath(Vertex<Airport, Airline *> *origin, std::vector<Vertex<Airport, Airline *> *> destinations) const {
	for (auto v: flights.getVertexSet()) {
		v->setVisited(false);
	}

	std::vector<Vertex<Airport, Airline *> *> path;
	std::unordered_map<u_int16_t, u_int16_t> previous;
	std::queue<Vertex<Airport, Airline *> *> q;
	q.push(origin);
	origin->setVisited(true);

	while (!q.empty()) {
		auto v = q.front();
		q.pop();

		if (std::find(destinations.begin(), destinations.end(), v) != destinations.end()) { // If v is one of the possible destinations
			auto buf = v;
			while (true) {
				path.push_back(buf);
				if (buf == origin) {
					break;
				}
				uint16_t prevCode = previous[buf->getInfo().getCode()];
				buf = this->searchAirportByCode.at(prevCode);
			}

			std::reverse(path.begin(), path.end());
			return path;
		} else {
			for (auto e: v->getAdj()) {
				auto w = e.getDest();
				if (!w->isVisited()) {
					w->setVisited(true);
					q.push(w);
					previous[w->getInfo().getCode()] = v->getInfo().getCode();
				}
			}
		}
	}

	return path; // No path found, so it returns the empty vector.
}
