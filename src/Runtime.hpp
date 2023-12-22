#ifndef AED2324_PRJ2_G23_RUNTIME_HPP
#define AED2324_PRJ2_G23_RUNTIME_HPP

#include "data/Data.hpp"

class Runtime {
private:
  Data *data;

  void processArgs(vector<std::string> args);
  
  void countAll();

public:
  explicit Runtime(Data *data);
  [[noreturn]] void run();
};

#endif // AED2324_PRJ2_G23_RUNTIME_HPP
