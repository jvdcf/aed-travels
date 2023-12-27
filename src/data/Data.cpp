#include "Data.hpp"
#include "Airline.hpp"
#include "Airport.hpp"
#include <cstdint>
#include <cstdlib>
#include <string>
#include <iostream>
#include <unordered_set>

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
