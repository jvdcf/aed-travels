#ifndef AED2324_PRJ2_G23_RUNTIME_HPP
#define AED2324_PRJ2_G23_RUNTIME_HPP

#include "data/Data.hpp"
#include <vector>

class Runtime {
private:
	Data *data;

	void processArgs(std::vector<std::string> args);

	void countAll();
	void displayAirport(Vertex<Airport, Airline*>* v_ap, bool full, unsigned k);
  void displayAirline(Airline &al);
  void essentialAirports();
  void greatestAirport(int k);
  void bestFlight(std::vector<std::string> args);
	void maxTrip();

public:
	explicit Runtime(Data *data);

	[[noreturn]] void run();
};

#endif // AED2324_PRJ2_G23_RUNTIME_HPP
