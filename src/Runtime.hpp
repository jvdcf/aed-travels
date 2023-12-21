#ifndef AED2324_PRJ2_G23_RUNTIME_HPP
#define AED2324_PRJ2_G23_RUNTIME_HPP


#include "data/Data.hpp"
#include "Process.hpp"

class Runtime {
private:
    Data data;

    void process_args(Process p);
    void handle_process(Process p);

public:
    Runtime(Data data);
    void run();
};


#endif //AED2324_PRJ2_G23_RUNTIME_HPP
