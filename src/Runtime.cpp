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
                  << "    display_airport:takes 1/2 arguments:    display_airport <airport_code> [-f | --full]\n"
                  << "        Displays information about an airport, optionally displaying all flight information.\n\n"
                  << "    greatest_airport: takes 0/2 arguments:  greatest_airport (-n <index>)\n"
                  << "        Displays the airport with the most flights (including incoming and outgoing) or the nth, one, using flag '-n'.\n\n";
        return;
    }

    if (args[0] == "list_counts") {
        countAll();
        return;
    }

    if (args[0] == "display_airport") {
        vector<string> local_args;
        for (int i = 1; i < args.size(); ++i) {
            local_args.push_back(args[i]);
        }
        displayAirport(local_args);
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

void Runtime::displayAirport(std::vector<std::string> args) {
    try {
        uint16_t code = Airport::codeToHash(args[0]);
        Vertex<Airport, Airline *> *v_ap = data->getAirportsByCode().at(code);
        Airport ap = v_ap->getInfo();
        std::cout << "Airport " << ap.codeToString(ap.getCode()) << ":\n"
                  << "  Name        : " << ap.getName() << ";\n"
                  << "  Location    : " << ap.getCity() << "/" << ap.getCountry() << ";\n"
                  << "  Coordinates : " << "Lat: " << ap.getLatitude() << " Long: " << ap.getLongitude() << ";"
                  << std::endl;
        auto edg = v_ap->getAdj();
        std::set<uint16_t> als;
        std::set<uint16_t> dst;
        std::set<std::string> countries;
        for (auto e: edg) {
            als.insert(e.getInfo()->getCode());
            dst.insert(e.getDest()->getInfo().getCode());
            countries.insert(e.getDest()->getInfo().getCountry());
        }
        std::cout << "Statistics: \n"
                  << "  Number of flights     : " << edg.size() << ";\n"
                  << "  Number of airlines    : " << als.size() << ";\n"
                  << "  Number of destinations: " << dst.size() << ";\n"
                  << "  Number of countries   : " << countries.size() << ";\n"
                  << std::endl;
        if (args.size() == 2) {
            std::string flag = args[1];
            if (flag == "--full" || flag == "-f") {
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
            } else {
                std::cerr << "ERROR   : " << "unknown argument " << args[1] << "." << std::endl;
            }
        } else if (args.size() == 1) {
            return;
        } else {
            std::cerr << "ERROR   : " << "tried to provide " << args.size()
                      << " arguments, but this function takes either 1 or 2." << std::endl;
        }
    } catch (exception &e) {
        std::cerr << "ERROR   : argument " << args[0] << "is not a valid airport code!" << std::endl;
    }
    return;
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
