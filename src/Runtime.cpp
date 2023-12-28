#include "Runtime.hpp"
#include "data/Airline.hpp"
#include "data/Airport.hpp"
#include <array>
#include <exception>
#include <iostream>
#include <ostream>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>

Runtime::Runtime(Data *data) { this->data = data; }

[[noreturn]] void Runtime::run() {
	std::string in;
	std::istringstream stream;
	std::string buf;
	std::vector<std::string> line;

	std::cout << "Welcome to FINS: Fins Is Not Skyscanner." << std::endl
              << "Type 'help' to learn more." << std::endl;

	while (true) {
		std::cout << "> ";
		getline(std::cin, in);
		stream = std::istringstream(in);
		while (std::getline(stream, buf, ' ')) {
			line.push_back(buf);
			buf.clear();
		}
		if (line.empty()) {
			in.clear();
			continue;
		}
		processArgs(line);
		in.clear();
		line.clear();
	}
}

void Runtime::processArgs(vector<std::string> args) {
    if (args[0] == "quit") {
        std::cout << "Quitting..." << std::endl;
        std::exit(0);
    }

    if (args[0] == "help") {
        std::cout << "The available commands are:\n"
                  << "    quit\n"
                  << "        Quits the program.\n\n"
                  << "    help\n"
                  << "        Prints this help.\n\n"
                  << "    list_counts\n"
                  << "        Counts the global number of airports, airlines and flights.\n\n"
                  << "    display_airport <airport_code> [-f | --full]\n"
                  << "        Displays information about an airport, optionally displaying all flight information.\n\n"
                  << "    display_airline <airline_code>\n"
                  << "        Displays information about an airline and their number of flights.\n\n"
				  << "    display_city <city_name>\n"
				  << "        Displays information about a city.\n\n"
                  << "    essential_airports\n"
                  << "        Displays all essential airports codes to the network's circulation capability.\n\n"
                  << "    greatest_airport (-n <index>)\n"
                  << "        Displays the airport or the first n airports (using flag '-n') with the most flights (including incoming and outgoing).\n\n"
                  << "    best_flight -ac|-an|-ci|-co <source> -ac|-an|-ci|-co <destination>\n"
				  << "        Displays the best flight options for a trip.\n"
				  << "        The arguments can be an Airport Code (-ac), an Airport Name (-an), a City (-ci) or the coordinate values (-co) as <latitude> <longitude>.\n\n"
                  << "    max_trip\n"
                  << "        Displays the flight trip(s) with the greatest number of stops.\n\n";
        return;
    }

    if (args[0] == "list_counts") {
        countAll();
        return;
    }

	if (args[0] == "display_airport") {
        if (args.size() <= 1 | args.size() > 5) {
            std::cerr << "ERROR   : " << "display_airport takes at least one and up to 4 arguments." << std::endl;
            return;
        }

        Vertex<Airport, Airline *> *v_ap;
        try {
            uint16_t code = Airport::codeToHash(args[1]);
            v_ap = data->getAirportsByCode().at(code);
        } catch (exception &e) {
            std::cerr << "ERROR   : " << "argument " << args[1] << " is not a valid airport code!" << std::endl;
            return;
        }

        bool full = false;
        int k = 1;
        for (int i = 2; i < args.size(); ++i) {
            std::string flag = args[i];

            if (flag == "--full" || flag == "-f") {
                full = true;

            } else if (flag == "-k") {
                i++;
                try {
                    k = std::stoi(args[i]);
                } catch (exception &e) {
                    std::cerr << "ERROR   : " << "argument " << args[i] << " is not a valid integer!" << std::endl;
                    return;
                }

            } else {
                std::cerr << "ERROR   : " << "unknown argument " << args[i] << "." << std::endl;
                return;
            }
        }

        displayAirport(v_ap, full, k);
        return;
    }

	if (args[0] == "display_airline") {
		if (args.size() != 2) {
			std::cerr << "ERROR   : " << "display_airline takes exactly 1 argument." << std::endl;
			return;
		}

		Airline al;
		try {
			uint16_t code = Airport::codeToHash(args[1]);
			al = data->getAirlines().at(code);
		} catch (exception &e) {
			std::cerr << "ERROR   : " << "argument " << args[1] << " is not a valid airline code!" << std::endl;
			return;
		}

		displayAirline(al);
		return;
	}
  
	if (args[0] == "display_city") {
		if(args.size() <= 1) {
			std::cerr << "ERROR   : display_city takes one argument." << std::endl;
			return;
		}
		for (auto itr = args.begin() + 1; itr + 1 != args.end();) { // This loop groups the city names with spaces in one single argument. Ex: {"Sao", "Paulo"} --> {"Sao Paulo"}
			*itr += ' ';
			*itr += *(itr + 1);
			itr = args.erase(std::find(args.begin(), args.end(), *(itr + 1))) - 1;
		}
		displayCity(args[1]);
		return;
	}

	if (args[0] == "essential_airports") {
		essentialAirports();
		return;
	}

	if (args[0] == "greatest_airport") {
		if (args.size() == 2 || args.size() > 3) {
			std::cerr << "ERROR   : " << "greatest_airport takes either 0 or 2 arguments." << std::endl;
			return;
		}
		if (args.size() == 1) return greatestAirport(1);
		if (args[1] == "-n") {
			int k;
			try {
				k = std::stoi(args[2]);
			} catch (exception &e) {
				std::cerr << "ERROR   : " << "argument " << args[2] << " is not a valid integer!" << std::endl;
				return;
			}
			greatestAirport(k);
			return;
		} else {
			std::cerr << "ERROR   : " << "unknown argument " << args[1] << "." << std::endl;
			return;
		}
	}

	if (args[0] == "best_flight") {
		for (auto itr = args.begin() + 2; itr + 1 != args.end();) {
			// This loop groups the city names with spaces in one single argument. Ex: {"Sao", "Paulo"} --> {"Sao Paulo"}
			if ((itr + 1)->at(0) == '-' or itr->at(0) == '-' or (itr->at(0) > '0' and itr->at(0) < '9')) {
				++itr;
				continue;
			}
			*itr += ' ';
			*itr += *(itr + 1);
			itr = args.erase(std::find(args.begin(), args.end(), *(itr + 1))) - 1;
		}
		if (args.size() < 5 or args.size() > 7) {
			std::cerr << "ERROR: best_flight takes 4/5/6 arguments." << std::endl;
			return;
		}
		bestFlight(args);
		return;
	}

    if (args[0] == "max_trip") {
        maxTrip();
        return;
    }

    std::cerr << "ERROR: No such command " << args[0]
              << ". Try typing 'help' to know the available commands."
              << std::endl;
}

// =====================================================================

void Runtime::countAll() {
	std::array<unsigned, 3> res = data->countAll();
	std::cout << "Global number of:\n"
			  << "  Airports: " << res[0] << '\n'
			  << "  Airlines: " << res[1] << '\n'
			  << "  Flights:  " << res[2] << '\n';
}

void Runtime::displayAirport(Vertex<Airport, Airline*>* v_ap, bool full, unsigned k) {
    Airport ap = v_ap->getInfo();
    std::cout << "Airport " << Airport::codeToString(ap.getCode()) << ":\n"
              << "  Name        : " << ap.getName() << ";\n"
              << "  Location    : " << ap.getCity() << "/" << ap.getCountry() << ";\n"
              << "  Coordinates : " << "Lat: " << ap.getLatitude() << " Long: " << ap.getLongitude() << ";"
              << std::endl;

    auto edg = v_ap->getAdj();
    std::set<uint16_t> als;
    std::set<std::string> countries;
    for (auto e: edg) {
        als.insert(e.getInfo()->getCode());
        countries.insert(e.getDest()->getInfo().getCountry());
    }

    std::cout << "Statistics: \n"
              << "  Number of flights                  : " << edg.size() << ";\n"
              << "  Number of airlines                 : " << als.size() << ";\n";

    if (k != 0) {
        std::cout << "  Number of destinations with " << k << " stops: "
                  << data->destinationsAtKStops(v_ap, ++k) << ";\n";
    } else {
        std::cout << "  Number of destinations             : "
                  << data->destinationsAtKStops(v_ap, 1) << ";\n";
    }
    std::cout << "  Number of countries                : " << countries.size() << ";\n"
              << std::endl;

    if (full) {
        std::cout << "Flights:" << std::endl;
        for (auto alcode: als) {
            std::cout << "  Airline " << Airline::codeToString(alcode) << ":" << std::endl;
            for (auto e: edg) {
                if (e.getInfo()->getCode() == alcode) {
                    std::cout << "    Destination: " << Airport::codeToString(e.getDest()->getInfo().getCode())
                              << std::endl;
                }
            }
        }
    }
}


void Runtime::displayAirline(Airline &al) {
	std::cout << "Airline " << al.getCodeStr() << ":\n"
			  << "  Name        : " << al.getName() << ";\n";

	if (!al.getAlias().empty() && al.getAlias() != "_") {
		std::cout << "  Callsign    : " << al.getAlias() << ";\n";
	}

	std::cout << "  Country     : " << al.getCountry() << ";\n"
			  << std::endl;

	unsigned flights = data->flightsPerAirline(al.getCode());
	std::cout << "Statistics: \n"
			  << "  Number of flights: " << flights << ";\n"
			  << std::endl;
}

void Runtime::essentialAirports() {
	std::unordered_set<uint16_t> res = data->essentialAirports();
	unsigned i = 0;

	std::cout << res.size() << " essential airports found: (Articulation points of the graph)" << std::endl;

	for (const auto &ap: res) {
		std::cout << "  " << Airport::codeToString(ap) << " ";
		i++;
		if (i % 10 == 0) std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;
}

void Runtime::displayCity(const std::string& city) {
	auto airports = data->searchByCity(city);
	if (airports.empty()) {
		std::cerr << "ERROR   : there is no city with such name." << std::endl;
		return;
	}

	std::set<std::string> countries;
	unsigned n_flights = 0;

	for (auto v: airports) {
		n_flights += v->getAdj().size();
		for (auto e: v->getAdj()) {
			countries.insert(e.getDest()->getInfo().getCountry());
		}
	}

	std::cout << "City   : " << city << std::endl;
	std::cout << "Country: " << airports[0]->getInfo().getCountry() << std::endl << std::endl;

	std::cout << "Statistics:" << std::endl;
	std::cout << "  Number of reachable countries: " << countries.size() << std::endl;
	std::cout << "  Number of flights            : " << n_flights << std::endl << std::endl;

	std::cout << "Airports:" << std::endl;
	for (auto v: airports) {
		std::cout << "  " << v->getInfo().getCodeStr() << " - " << v->getInfo().getName() << std::endl;
	}
}

void Runtime::greatestAirport(int k) {
	auto res = data->greatestAirport(k);
	std::string name = res->getInfo().getName();
	uint16_t code = res->getInfo().getCode();
	unsigned flights = res->getAdj().size();

	std::cout << "Airport " << name << " (" << Airport::codeToString(code) << ')'
			  << " with " << flights << " flights"
			  << std::endl << std::endl;
}

void Runtime::bestFlight(std::vector<std::string> args) {
	std::vector<Vertex<Airport, Airline *> *> sources;
	std::vector<Vertex<Airport, Airline *> *> destinations;

	for (unsigned i = 1; i < args.size(); ++i) {
		if (args[i] == "-ac") { // -------------------------------------------------------------------------------------
			++i;
			try {
				if (sources.empty()) {
					sources.push_back(data->getAirportsByCode().at(Airport::codeToHash(args[i])));
				} else {
					destinations.push_back(data->getAirportsByCode().at(Airport::codeToHash(args[i])));
				}
			} catch (exception &exception) {
				std::cerr << "ERROR: " << args[i] << " is not an Airport code." << std::endl;
				return;
			}
			continue;
		} else if (args[i] == "-an") { // ------------------------------------------------------------------------------
			++i;
			try {
				if (sources.empty()) {
					sources.push_back(data->getAirportsByName().at(args[i]));
				} else {
					destinations.push_back(data->getAirportsByName().at(args[i]));
				}
			} catch (exception &exception) {
				std::cerr << "ERROR: " << args[i] << " is not an Airport name." << std::endl;
				return;
			}
			continue;
		} else if (args[i] == "-ci") { // ------------------------------------------------------------------------------
			++i;
			auto buf = data->searchByCity(args[i]);
			if (buf.empty()) {
				std::cerr << "ERROR: " << args[i] << " is not a City name." << std::endl;
				return;
			}
			if (sources.empty()) {
				sources = buf;
			} else {
				destinations = buf;
			}
		} else if (args[i] == "-co") { // ------------------------------------------------------------------------------
			++i;
			float latitude, longitude;
			try {
				latitude = std::stof(args[i]);
			} catch (exception &e) {
				std::cerr << "ERROR: " << args[i] << " is not a valid latitude." << std::endl;
				return;
			}
			++i;
			try {
				longitude = std::stof(args[i]);
			} catch (exception &e) {
				std::cerr << "ERROR: " << args[i] << " is not a valid longitude." << std::endl;
				return;
			}

			if (latitude < -90.0 or latitude > 90.0) {
				std::cerr << "ERROR: " << args[i] << " is not a valid latitude." << std::endl;
				return;
			}
			if (longitude < -180.0 or longitude > 180.0) {
				std::cerr << "ERROR: " << args[i] << " is not a valid longitude." << std::endl;
				return;
			}

			if (sources.empty()) {
				sources.push_back(data->nearestAirport(latitude, longitude));
			} else {
				destinations.push_back(data->nearestAirport(latitude, longitude));
			}
		} else {
			std::cerr << "ERROR: unknown argument " << args[i] << "." << std::endl;
			return;
		}
	}

	std::vector<std::string> bf = data->bestFlight(sources, destinations);
	std::cout << "The best flight option is:" << std::endl;
	for (unsigned i = 1; i < bf.size(); i++) {
		std::cout << "  " << bf[i - 1] << " --> " << bf[i] << std::endl;
	}
}

void Runtime::maxTrip() {
	std::vector<Vertex<Airport, Airline *> *> origins;
	std::vector<Vertex<Airport, Airline *> *> destinations;
	int stops = data->maxTrip(origins, destinations);

	std::cout << "Maximum trip:" << std::endl
			  << "  Number of stops: " << stops << std::endl
			  << "  Trips:" << std::endl;

	for (unsigned i = 0; i < origins.size(); ++i) {
		std::cout << "    " << origins[i]->getInfo().getCodeStr() << " --> " << destinations[i]->getInfo().getCodeStr()
				  << std::endl;
	}
}
