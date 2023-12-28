#include "Data.hpp"
#include "Airline.hpp"
#include "Airport.hpp"
#include <cstdlib>
#include <string>
#include <iostream>
#include <unordered_set>
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
  Vertex<Airport,Airline*>* src = searchAirportByCode[source_code];
  Vertex<Airport,Airline*>* dst = searchAirportByCode[dest_code];
  Airline* air = &searchAirlines[airline_code];
  float distance = src->getInfo().disToOther(dst->getInfo());
  flights.addEdge(src, dst, distance, air);
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

std::vector<Vertex<Airport, Airline *> *> Data::searchByCity(const std::string &city) const {
	std::vector<Vertex<Airport, Airline *> *> res;
	for (auto v: flights.getVertexSet()) {
		if (v->getInfo().getCity() == city) {
			res.push_back(v);
		}
	}
	return res;
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

void dfs_art(Graph<Airport, Airline*>* g, Vertex<Airport, Airline*>* v, std::stack<uint16_t>& s, std::unordered_set<uint16_t>& l, int &i);
std::unordered_set<uint16_t> Data::essentialAirports() {
    for (auto v: flights.getVertexSet()) {
        v->setVisited(false);
    }
    std::unordered_set<uint16_t> res;
    int index = 0;


    for (auto v: flights.getVertexSet()) {
        if (!v->isVisited()) {
            stack<uint16_t> s;
            dfs_art(&flights, v, s, res, index);
        }
    }
    return res;

}

template <typename T>
bool stackContains(std::stack<T> s, T elem);
void dfs_art(Graph<Airport, Airline*>* g, Vertex<Airport, Airline*>* v, std::stack<uint16_t>& s, std::unordered_set<uint16_t>& l, int &i) {
    int children = 0;
    v->setLow(++i);
    v->setNum(v->getLow());
    v->setVisited(true);
    s.push(v->getInfo().getCode());

    for (const Edge<Airport, Airline*> e: v->getAdj()) {
        Vertex<Airport, Airline*>* w = e.getDest();
        if (!w->isVisited()) {                                               // Tree edge
            children++;
            dfs_art(g, w, s, l, i);
            v->setLow(min(w->getLow(), v->getLow()));

            if ((v->getNum() != 1) && (w->getLow() >= v->getNum())) {       // Articulation point
                l.insert(v->getInfo().getCode());
            }

        } else if (stackContains(s, w->getInfo().getCode())) {                                                            // Back edge
            v->setLow(min(w->getNum(), v->getLow()));
        }
    }

    if ((v->getNum() == 1) && (children > 1)) {                             // Root special case
        l.insert(v->getInfo().getCode());
    }

    s.pop();
}

template <typename T>
bool stackContains(const std::stack<T> s, T elem) {
    std::stack<T> tmp = s;
    while (!tmp.empty()) {
        if (tmp.top() == elem) {
            return true;
        }
        tmp.pop();
    }
    return false;
}

Vertex<Airport, Airline*>* Data::greatestAirport(unsigned int k) {
    std::vector<Vertex<Airport,Airline*>*> v = flights.getVertexSet();

    std::sort(v.begin(), v.end(),
              [](Vertex<Airport,Airline*>* a, Vertex<Airport,Airline*>* b) {
        return a->getAdj().size() + a->getIndegree() > b->getAdj().size() + b->getIndegree();
    });

    return v[k];
}
