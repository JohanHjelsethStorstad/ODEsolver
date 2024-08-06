#pragma once
#include "FieldGenerator.h"
#include "../src/structures/Point.h"
#include "../src/ButcherTableau.h"
#include "../src/PrimeFieldInferation.h"
#include "../src/ODE.h"
#include <vector>
#include <string>
#include <memory>
#include <map>

namespace ODE::Tests {
    struct FieldGeneratorInfo;

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
        std::string name = "Test";
        std::vector<Structures::Point<double>> startPoints;
        std::vector<std::shared_ptr<BucherTableau::ButcherTableau>> schemes;
        std::vector<std::shared_ptr<PrimeFieldInferation::PrimeFieldInferationScheme>> inferationSchemes;
        TestConfig() = default;
        const TestConfig& loadFromFile(std::string configFileName);
        FieldGeneratorInfo fieldGeneratorInfo;
    };

    enum class FieldGeneratorType {
        RANDOM,
        FUNCTION,
        LOAD_FROM_FILE
    };

    const std::map<std::string, FieldGeneratorType> FieldGeneratorTypeMap = {
        {"Random", FieldGeneratorType::RANDOM},
        {"Function", FieldGeneratorType::FUNCTION},
        {"LOAD_FROM_FILE", FieldGeneratorType::LOAD_FROM_FILE}
    };

    const std::map<std::string, ODE<2>> PreProgrammedODEMap = {
        {"HarmonicOcillator", ODE<2>::HarmonicOscillator(1)},
        {"Circle", ODE<2>::Circle()},
        {"Identity", ODE<2>::Identity()},
        {"CrossIdentity", ODE<2>::CrossIdentity()}
    };

    struct FieldGeneratorInfo {
        FieldGeneratorType type;

        //For RANDOM
        FieldGeneratorRandomBounds bounds;

        //For FUNCTION
        ODE<2> ode;

        //For LOAD_FROM_FILE
        std::string fileName;
    };
}