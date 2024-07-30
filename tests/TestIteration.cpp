#include "TestIteration.h"
#include "FieldGenerator.h"
#include "../src/Store.h"
#include <memory>
#include <vector>
#include <iostream>

void ODE::Tests::runTestSuite() {
    const TestConfig config; //Default values
    auto inferNearest = std::make_shared<PrimeFieldInferation::PrimeFieldInferationSchemeNearest>(PrimeFieldInferation::PrimeFieldInferationSchemeNearest());
    auto inferWeightedAverage = std::make_shared<PrimeFieldInferation::PrimeFieldInferationSchemeWeightedAverage>(PrimeFieldInferation::PrimeFieldInferationSchemeWeightedAverage());

    auto Euler = std::make_shared<BucherTableau::ExplicitButcherTableau<1>>(BucherTableau::ExplicitButcherTableau<1>::Euler());
    auto RK4 = std::make_shared<BucherTableau::ExplicitButcherTableau<4>>(BucherTableau::ExplicitButcherTableau<4>::RungeKutta4());
    auto RK3 = std::make_shared<BucherTableau::ExplicitButcherTableau<4>>(BucherTableau::ExplicitButcherTableau<4>::RungeKutta3());
    auto Heun = std::make_shared<BucherTableau::ExplicitButcherTableau<2>>(BucherTableau::ExplicitButcherTableau<2>::Heun());

    std::function<void(std::vector<Structures::Arrow<double>>, std::string)> runTestOnAllMethods {
        [&](std::vector<Structures::Arrow<double>> primeField, std::string fieldName) {
            std::vector<std::pair<std::vector<Structures::Point<double>>, std::string>> trajectories;
            std::vector<std::shared_ptr<BucherTableau::IButcherTableau>> schemes = {Euler, RK4, RK3, Heun};
            for (const auto& scheme : schemes) {
                trajectories.push_back({TestIteration(IterationScheme(
                    primeField,
                    scheme,
                    inferWeightedAverage
                ), config.dt, config.iterations).test(), scheme->getName() + " Weighted Average"});
                trajectories.push_back({TestIteration(IterationScheme(
                    primeField,
                    scheme,
                    inferNearest
                ), config.dt, config.iterations).test(), scheme->getName() + " Nearest"});
            }
            storeTest(fieldName, primeField, trajectories);
        }
    };

    std::vector<Structures::Arrow<double>> randomPrimeField = FieldGeneratorRandom(
        config.fieldDelta, 
        config.window,
        config.bounds
    ).generateField();

    runTestOnAllMethods(randomPrimeField, "Random");

    std::vector<Structures::Arrow<double>> functionPrimeField1 = FieldGeneratorFunction(
        config.fieldDelta,
        config.window,
        [](Structures::Point<double> point) {
            return Structures::Point<double> {point.y, -point.x};
        }
    ).generateField();

    runTestOnAllMethods(functionPrimeField1, "Function (x, y) -> (y, -x)");

    std::vector<Structures::Arrow<double>> functionPrimeField2 = FieldGeneratorFunction(
        config.fieldDelta,
        config.window,
        [](Structures::Point<double> point) {
            return Structures::Point<double> {2*point.y + point.x, point.x + 3*point.y};
        }
    ).generateField();

    runTestOnAllMethods(functionPrimeField2, "Function (x, y) -> (2y + x, x + 3y)");
}

void ODE::Tests::storeTest(std::string name, std::vector<Structures::Arrow<double>> primeField, std::vector<std::pair<std::vector<Structures::Point<double>>, std::string>> trajectories) {
    Store::Store store (name);
    store.write("Prime field");
    store.store(primeField, "Prime");
    store.write("Trajectory 1");
    for (const auto& [trajectory, tag] : trajectories) {
        store.store(trajectory, tag);
    }
}

std::vector<Structures::Point<double>> ODE::Tests::TestIteration::test() {
    std::vector<Structures::Point<double>> points;
    Structures::Point<double> point = {1.5, 1.5};
    for (int i = 0; i < this->iterations; i++) {
        point = this->scheme.step(point, this->dt);
        points.push_back(point);
    }
    return points;
}