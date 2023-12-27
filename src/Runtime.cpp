#include "Runtime.hpp"
#include "data/Airline.hpp"
#include "data/Airport.hpp"
#include <array>
#include <cstdint>
#include <exception>
#include <iostream>
#include <ostream>
#include <set>
#include <sstream>
#include <vector>

Runtime::Runtime(Data *data) { this->data = data; }

[[noreturn]] void Runtime::run() {
  std::string in;
  std::istringstream stream;
  std::string buf;
  std::vector<std::string> line;

  std::cout << "Welcome to ___. Type 'help' to learn more." << std::endl;

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
              << "    quit:           takes 0 arguments:      quit\n"
              << "        Quits the program.\n\n"
              << "    help:           takes 0 arguments:      help\n"
              << "        Prints this help.\n\n"
              << "    list_counts:    takes 0 arguments:      list_counts\n"
              << "        Counts the global number of airports, airlines and flights.\n\n"
              << "    display_airport:takes 1/2/4 arguments:    display_airport <airport_code> [-f | --full] [-k <n_stops>]\n"
              << "        Displays information about an airport, optionally displaying all flight information and the number of destinations with k stops.\n\n"
    ;
    return;
  }

  if (args[0] == "list_counts") {
    countAll();
    return;
  }

  if (args[0] == "display_airport") {
    if (args.size() <= 1 | args.size() > 5) {
        std::cerr << "ERROR   : " << "display_airport takes up to 4 arguments." << std::endl;
      return;
    }

    Vertex<Airport, Airline*> *v_ap;
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

  std::cerr << "ERROR: No such command " << args[0]
            << ". Try typing 'help' to know the available commands."
            << std::endl;
}

// =====================================================================

void Runtime::countAll() {
  std::array<unsigned, 3>res = data->countAll();
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
              << "  Coordinates : " << "Lat: " << ap.getLatitude() << " Long: " << ap.getLongitude() << ";" << std::endl;

    auto edg = v_ap->getAdj();
    std::set<uint16_t> als;
    std::set<std::string> countries;
    for (auto e : edg) {
      als.insert(e.getInfo()->getCode());
      countries.insert(e.getDest()->getInfo().getCountry());
    }

    std::cout << "Statistics: \n" 
              << "  Number of flights                  : " << edg.size() << ";\n"
              << "  Number of airlines                 : " << als.size() << ";\n";

    if (k != 0) {
        std::cout << "  Number of destinations with " << k << " stops: "
                  << data->destinationsAtKStops(v_ap, k) << ";\n";
    } else {
        std::cout << "  Number of destinations             : "
              << data->destinationsAtKStops(v_ap, 0) << ";\n";
    }
    std::cout << "  Number of countries                : " << countries.size() << ";\n"
              << std::endl;

    if (full) {
      std::cout << "Flights:" << std::endl;
      for (auto alcode : als) {
        std::cout << "  Airline " << Airline::codeToString(alcode) << ":" << std::endl;
        for (auto e : edg) {
          if (e.getInfo()->getCode() == alcode) {
            std::cout << "    Destination: " << Airport::codeToString(e.getDest()->getInfo().getCode()) << std::endl;
          }
        }
      }
    }
}



