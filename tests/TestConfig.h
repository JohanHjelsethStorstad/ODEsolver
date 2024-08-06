#pragma once
#include "FieldGenerator.h"
#include "../src/structures/Point.h"
#include "../src/ButcherTableau.h"
#include "../src/PrimeFieldInferation.h"
#include <vector>
#include <string>
#include <memory>

namespace ODE::Tests {
    class TestConfig {
    public:
        int iterations = 1000;
        double dt = 0.2;
        double fieldDelta = 0.1;
        FieldGeneratorWindow window = {20, 20, -10, -10};
        FieldGeneratorRandomBounds bounds = {-10, 10};
        std::string name = "Test";
        std::vector<Structures::Point<double>> startPoints = {{1.5, 1.5}};
        std::vector<std::shared_ptr<BucherTableau::ButcherTableau>> schemes = {
            std::make_shared<BucherTableau::ExplicitButcherTableau<4>>(BucherTableau::ExplicitButcherTableau<4>::RungeKutta4())
        };
        std::vector<std::shared_ptr<PrimeFieldInferation::PrimeFieldInferationScheme>> inferationSchemes = {
            std::make_shared<PrimeFieldInferation::PrimeFieldInferationSchemeNearest>(PrimeFieldInferation::PrimeFieldInferationSchemeNearest())
        };
        TestConfig() = default;
        const TestConfig& loadFromFile(std::string configFileName);
    };
}