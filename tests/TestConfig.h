#pragma once
#include "FieldGenerator.h"
#include "../src/structures/Point.h"
#include "../src/ButcherTableau.h"
#include "../src/PrimeFieldInferation.h"
#include <vector>
#include <string>
#include <memory>
#include <map>

namespace ODE::Tests {
    class TestConfig {
    private:
        const std::map<std::string, std::shared_ptr<BucherTableau::ButcherTableau>> availableTableaus = {
            {"Euler", std::make_shared<BucherTableau::ExplicitButcherTableau<1>>(BucherTableau::ExplicitButcherTableau<1>::Euler())},
            {"RK4", std::make_shared<BucherTableau::ExplicitButcherTableau<4>>(BucherTableau::ExplicitButcherTableau<4>::RungeKutta4())},
            {"RK3", std::make_shared<BucherTableau::ExplicitButcherTableau<4>>(BucherTableau::ExplicitButcherTableau<4>::RungeKutta3())},
            {"Heun", std::make_shared<BucherTableau::ExplicitButcherTableau<2>>(BucherTableau::ExplicitButcherTableau<2>::Heun())}
        };
        const std::map<std::string, std::shared_ptr<PrimeFieldInferation::PrimeFieldInferationScheme>> availableInferationSchemes = {
            {"Nearest", std::make_shared<PrimeFieldInferation::PrimeFieldInferationSchemeNearest>(PrimeFieldInferation::PrimeFieldInferationSchemeNearest())},
            {"Weighted Average", std::make_shared<PrimeFieldInferation::PrimeFieldInferationSchemeWeightedAverage>(PrimeFieldInferation::PrimeFieldInferationSchemeWeightedAverage())}
        };
    public:
        int iterations = 1000;
        double dt = 0.2;
        double fieldDelta = 0.1;
        FieldGeneratorWindow window;
        FieldGeneratorRandomBounds bounds;
        std::string name = "Test";
        std::vector<Structures::Point<double>> startPoints;
        std::vector<std::shared_ptr<BucherTableau::ButcherTableau>> schemes;
        std::vector<std::shared_ptr<PrimeFieldInferation::PrimeFieldInferationScheme>> inferationSchemes;
        TestConfig() = default;
        const TestConfig& loadFromFile(std::string configFileName);
    };
}