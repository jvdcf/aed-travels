#include "Process.hpp"
#include <string>
#include <vector>

/**
 * @brief Constructs a request of a certain type.
 * @details This request is not yet completed, as the operands are still to be added.
 * Theoretical Complexity: O(1).
 * @param t
 */
Process::Process(TypeOfRequest t) {
    type = t;
    operands = std::vector<std::string>();
}

/**
 * @brief Adds a string to the operands vector
 * @details Theoretical Complexity: O(1).
 * @param op
 */
void Process::addOperand(std::string op) {
    operands.push_back(op);
}

/**
 * @brief Accesses the type of request.
 * @details Theoretical Complexity: O(1).
 * @return TypeOfRequest
 */
TypeOfRequest Process::getType() {
    return type;
}

/**
 * @brief Accesses the vector of operands.
 * @details Theoretical Complexity: O(1).
 * @return Pointer to the vector of operands.
 */
std::vector<std::string>& Process::getOps() {
    return operands;
}