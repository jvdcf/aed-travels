#include "Parser.hpp"
#include "data/Airline.hpp"
#include "data/Airport.hpp"
#include "data/Data.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split_csv(std::string s) {
    std::stringstream ss(s);
    std::vector<std::string> res;
    std::string buf;
    while (getline(ss,buf,',')) {
        res.push_back(buf);
        buf.clear();
    }
    return res;
}

Data Parser::parse(const std::string& airports, const std::string& airlines, const std::string& flights) {
    Data res = Data();    
    parseAirports(res, airports);
    parseAirlines(res, airlines);
    parseFlights(res, flights);
    return res;
}

void Parser::parseAirports(Data &data, const std::string& csv) {
    std::string line;
    std::fstream s(csv);
    std::getline(s,line);
    while (std::getline(s,line)) {
        auto csv_fields = split_csv(line);
        if (csv_fields.size() != 6) {
            std::cerr << "WARNING: Invalid line in file that stores the airports' information." << std::endl;
            std::cerr << "INFO    : If you only see one warning per file, you might have a trailing empty line." << std::endl;
            continue;
        }
        Airport entry = Airport(csv_fields[0], csv_fields[1], csv_fields[2], csv_fields[3], std::stof(csv_fields[4]), std::stof(csv_fields[5]));
        line.clear();
        data.loadAirport(entry);
    }
}

void Parser::parseAirlines(Data &data, const std::string& csv) {
    std::string line;
    std::fstream s(csv);
    std::getline(s,line);
    while (std::getline(s,line)) {
        auto csv_fields = split_csv(line);
        if (csv_fields.size() != 4) {
            std::cerr << "WARNING: Invalid line in file that stores the airlines' information." << std::endl;
            std::cerr << "INFO    : If you only see one warning per file, you might have a trailing empty line." << std::endl;
            continue;
        }
        Airline entry = Airline(csv_fields[0], csv_fields[1], csv_fields[2], csv_fields[3]);
        line.clear();
        data.loadAirline(entry);
    }
}

void Parser::parseFlights(Data &data, const std::string& csv) {
    std::string line;
    std::fstream s(csv);
    std::getline(s,line);
    while (std::getline(s,line)) {
        auto csv_fields = split_csv(line);
        if (csv_fields.size() != 3) {
            std::cerr << "WARNING : Invalid line in file that stores the flights' information." << std::endl;
            std::cerr << "INFO    : If you only see one warning per file, you might have a trailing empty line." << std::endl;
            continue;
        }
        line.clear();
        data.loadFlight(Airport::codeToHash(csv_fields[0]), Airport::codeToHash(csv_fields[1]), Airline::codeToHash(csv_fields[2]));
    }
}
