#include "IterationScheme.h"
#include <memory>
#include "../tests/TestIteration.h"

/**
 * @brief Runs the tests for the iteration scheme.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 */
int main(int argc, char* argv[]) {
    if (argc == 1) throw std::invalid_argument("No arguments provided. Must be test, ...");   
    if (argv[1] == std::string("test")) {
        if (argc == 2) throw std::invalid_argument("No test provided.");
        std::string testName = argv[2];
        ODE::Tests::runTestSuite(testName);
    } else {
        throw std::invalid_argument("Invalid argument provided.");
    }
    return 0;
}