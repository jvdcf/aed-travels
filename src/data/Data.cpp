#include "Data.hpp"
#include "Airline.hpp"
#include "Airport.hpp"
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

template<typename T, typename U>
int shortestPath(const Graph<T, U> &g, Vertex<T, U>* source, vector<Vertex<T, U> *> &destinations) {
    int depth = 0;
    for (auto v: g.getVertexSet()) {
        v->setVisited(false);
    }
    queue<Vertex<T, U>*> q;
    queue<Vertex<T, U>*> next;
    q.push(source);
    source->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        destinations.push_back(v);

        for (auto & e : v->getAdj()) {
            auto w = e.getDest();
            if ( ! w->isVisited() ) {
                next.push(w);

                w->setVisited(true);
            }
        }

        if (q.empty() && !next.empty()) {
            depth++;
            swap(q, next);
            destinations.clear();
        }
    }

    return depth;
}

int Data::maxTrip(std::vector<Vertex<Airport, Airline *> *> &origin,
				  std::vector<Vertex<Airport, Airline *> *> &destination) const {
    int maxDepth = 0;
    for (auto v: flights.getVertexSet()) {
        vector<Vertex<Airport, Airline *> *> destinations;
        int depth = shortestPath(flights, v, destinations);
        if (depth > maxDepth) {
            maxDepth = depth;
            origin.clear();
            destination.clear();
        }
        if (depth >= maxDepth) {
            for (auto d: destinations) {
                origin.push_back(v);
                destination.push_back(d);
            }
        }
    }

    return maxDepth;
}

unsigned Data::flightsPerAirline(uint16_t code) {
    unsigned count = 0;
    for (auto v: flights.getVertexSet()) {
        for (auto e: v->getAdj()) {
            if (e.getInfo()->getCode() == code) {
                count++;
            }
        }
    }
    return count;
}
