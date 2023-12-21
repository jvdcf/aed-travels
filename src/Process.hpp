/**
 * @file Process.hpp
 */
#ifndef AED2324_PRJ2_G23_PROCESS_HPP
#define AED2324_PRJ2_G23_PROCESS_HPP


#include <string>
#include <vector>

/**
* @brief Used to efficiently store the type of request.
*/
enum class TypeOfRequest {
    // TODO
};

/**
 * @brief Stores the user requests.
 */
class Process {
private:
    /// The type of request it was made.
    TypeOfRequest type;
    /// The arguments for the function.
    std::vector<std::string> operands;

public:
    explicit Process(TypeOfRequest t);
    void addOperand(std::string s);
    TypeOfRequest getType();
    std::vector<std::string>& getOps();
};


#endif //AED2324_PRJ2_G23_PROCESS_HPP
