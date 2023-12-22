#include "Runtime.hpp"
#include <array>
#include <iostream>
#include <sstream>

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
              << "        Counts the global number of airports, airlines and flights.\n\n";
    return;
  }

  if (args[0] == "list_counts") {
    countAll();
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
