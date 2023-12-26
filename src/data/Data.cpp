#include "Data.hpp"
#include "Airline.hpp"
#include "Airport.hpp"
#include <cstdint>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>

Data::Data() {
	this->searchAirportByCode = unordered_map<uint16_t, Vertex<Airport, Airline *> *>();
	this->searchAirportByName = unordered_map<std::string, Vertex<Airport, Airline *> *>();
	this->searchAirlines = unordered_map<uint16_t, Airline>();
}

void Data::loadAirport(Airport &airport) {
	auto v_ptr = flights.addVertex(airport);
	if (v_ptr == nullptr) {
		std::cerr << "ERROR   : There is something seriously wrong with the database: airport " << airport.getName()
				  << " is repeated multiple times" << std::endl;
		std::exit(1);
	}
	searchAirportByCode[airport.getCode()] = v_ptr;
	searchAirportByName[airport.getName()] = v_ptr;
}

void Data::loadAirline(Airline &airline) {
	searchAirlines[airline.getCode()] = airline;
}

void Data::loadFlight(uint16_t source_code, uint16_t dest_code, uint16_t airline_code) {
	Vertex<Airport, Airline *> *src = searchAirportByCode[source_code];
	Vertex<Airport, Airline *> *dst = searchAirportByCode[dest_code];
	Airline *air = &searchAirlines[airline_code];
	float distance = src->getInfo().disToOther(dst->getInfo());
	auto tmp = src->getAdj();
	tmp.push_back(Edge<Airport, Airline *>(dst, distance, air));
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

int Data::shortestPath(Vertex<Airport, Airline *> *origin, Vertex<Airport, Airline *> *destination) const {
	for (auto v: flights.getVertexSet()) {
		v->setVisited(false);
	}

	int res = 0;
	queue<Vertex<Airport, Airline *> *> q;
	q.push(origin);
	int countThisLevel = 1;
	origin->setVisited(true);

	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		countThisLevel--;

		if (v->getInfo() == destination->getInfo()) {
			return res;
		} else {
			for (auto e: v->getAdj()) {
				if (!e.getDest()->isVisited()) {
					v->setVisited(true);
					q.push(e.getDest());
				}
			}
		}

		if (countThisLevel == 0) {
			countThisLevel = (int) q.size();
			res++;
		}
	}

	return -1;
}

int Data::maxTrip(std::vector<Vertex<Airport, Airline *> *> &origin,
				  std::vector<Vertex<Airport, Airline *> *> &destination) const {
	std::vector<Vertex<Airport, Airline *> *> v = flights.getVertexSet();
	std::sort(v.begin(), v.end(), [](Vertex<Airport, Airline *> *a, Vertex<Airport, Airline *> *b) {
		return a->getInfo().getCode() < b->getInfo().getCode();
	});

	int distanceTable[v.size()][v.size()];
	int max = 0;
	for (unsigned i = 0; i < v.size(); ++i) {
		for (unsigned j = 0; j < v.size(); ++j) {
			distanceTable[i][j] = shortestPath(v[i], v[j]);
			if (distanceTable[i][j] > max) {
				origin.clear();
				destination.clear();
				max = distanceTable[i][j];
				origin.push_back(v[i]);
				destination.push_back(v[j]);
			} else if (distanceTable[i][j] == max) {
				origin.push_back(v[i]);
				destination.push_back(v[j]);
			}
		}
	}

	return max;
}
