#include "TestConfig.h"
#include <fstream>
#include <nlohmann/json.hpp>

void ODE::Tests::TestConfig::loadFromFile(std::string configFileName) {
    std::ifstream file{"/tests/configs/" + configFileName};
    if (!file.is_open()) {
        throw std::invalid_argument("Could not open file: " + configFileName);
    }

}