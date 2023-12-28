#include "lib/Graph.h"
#include "src/Parser.hpp"
#include "src/Runtime.hpp"
#include "src/data/Airline.hpp"
#include "src/data/Data.hpp"
#include <iostream>

void printError() {
    std::cerr
            << "USAGE: The program takes three files, with their specific flags "
               "prepending them. Example:\n\n"
            << "    fins -ap airports.csv -al airlines.csv -f "
               "flights.csv\n\n"
            << "Where '-ap' is the flag that specifies a CSV file which contains "
               "the list of airports\n"
            << "Where '-al' is the flag that specifies a CSV file which contains "
               "the list of airlines\n"
            << "Where '-f' is the flag that specifies a CSV file which contains "
               "the list of flights\n\n"
            << "DISCLAIMER: This program is tested for Linux only. As such, it "
               "only takes Linux-compatible CSV files on Linux. It might work on "
               "Windows, but that is untested.\n"
            << std::endl;
    std::exit(1);
}

bool isFlag(const std::string &arg) {
    return arg == "-ap" | arg == "-al" | arg == "-f";
}

int main(int argc, char **argv) {
    std::string airports;
    std::string airlines;
    std::string flights;

    if (argc != 7)
        printError();

    for (int i = 1; i < argc; i += 2) {
        if (std::string(argv[i]) == std::string("-ap")) {
            if (isFlag(std::string(argv[i + 1]))) break;
            airports = std::string(argv[i + 1]);
        }

        if (std::string(argv[i]) == std::string("-al")) {
            if (isFlag(std::string(argv[i + 1]))) break;
            airlines = std::string(argv[i + 1]);
        }

        if (std::string(argv[i]) == std::string("-f")) {
            if (isFlag(std::string(argv[i + 1]))) break;
            flights = std::string(argv[i + 1]);
        }
    }

    if (airports.empty() | airlines.empty() | flights.empty()) printError();

    Data data = Parser::parse(airports, airlines, flights);
    Runtime rt(&data);
    rt.run();
}
