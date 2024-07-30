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

    std::vector<Structures::Arrow<double>> randomPrimeField = FieldGeneratorRandom(
        config.fieldDelta, 
        config.window,
        config.bounds
    ).generateField();

    std::vector<Structures::Arrow<double>> function1PrimeField = FieldGeneratorFunction(
        config.fieldDelta, 
        config.window,
        [](Structures::Point<double> point) -> Structures::Point<double> {
            return {point.y, -point.x};
        }
    ).generateField();

    std::vector<Structures::Arrow<double>> function2PrimeField = FieldGeneratorFunction(
        config.fieldDelta, 
        config.window,
        [](Structures::Point<double> point) -> Structures::Point<double> {
            return {point.x + 2*point.y, point.x + point.y};
        }
    ).generateField();

    std::vector<Structures::Point<double>> test0 = TestIteration(IterationScheme(
        randomPrimeField,
        Euler,
        inferWeightedAverage
    ), config.dt, config.iterations).test();
    storeTest("Euler Weighted Average Random", randomPrimeField, test0);

    std::vector<Structures::Point<double>> test1 = TestIteration(IterationScheme(
        randomPrimeField,
        Euler,
        inferNearest
    ), config.dt, config.iterations).test();
    storeTest("Euler Nearest Random", randomPrimeField, test1);

    std::vector<Structures::Point<double>> test2 = TestIteration(IterationScheme(
        function1PrimeField,
        Euler,
        inferWeightedAverage
    ), config.dt, config.iterations).test();
    storeTest("Euler Weighted Average Function (x, y) -> (y, -x)", function1PrimeField, test2);

    std::vector<Structures::Point<double>> test3 = TestIteration(IterationScheme(
        function1PrimeField,
        Euler,
        inferNearest
    ), config.dt, config.iterations).test();
    storeTest("Euler Nearest Function (x, y) -> (y, -x)", function1PrimeField, test3);
}

void ODE::Tests::storeTest(std::string name, std::vector<Structures::Arrow<double>> primeField, std::vector<std::vector<Structures::Point<double>>> trajectories) {
    Store::Store store (name);
    store.write("Prime field");
    store.store(primeField);
    store.write("Trajectory 1");
    for (const auto& trajectory : trajectories) {
        store.store(trajectory);
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