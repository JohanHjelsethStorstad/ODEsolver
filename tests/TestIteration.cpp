#include "TestIteration.h"
#include "FieldGenerator.h"
#include "../src/Store.h"
#include "../src/DynamicalSystem.h"
#include <memory>
#include <vector>
#include <iostream>

std::function<void(std::vector<Structures::Arrow<double>>, std::string)> ODE::Tests::getRunner(
    const std::vector<std::shared_ptr<BucherTableau::IButcherTableau>>& schemes,
    const std::vector<std::shared_ptr<PrimeFieldInferation::PrimeFieldInferationScheme>>& inferationSchemes,
    const std::vector<Structures::Point<double>>& startPoints,
    const TestConfig& config
) {
    return [&](std::vector<Structures::Arrow<double>> primeField, std::string fieldName) {
        std::vector<std::pair<std::vector<Trajectory>, std::string>> trajectories;
        for (const auto& scheme : schemes) {
            for (const auto& inferationScheme : inferationSchemes) {
                trajectories.push_back({TestIteration(IterationScheme(
                    primeField,
                    scheme,
                    inferationScheme
                ), config.dt, config.iterations).test(startPoints), scheme->getName() + " " + inferationScheme->getName()});
            }
        }
        storeTest(fieldName, primeField, trajectories);
    };
}

void ODE::Tests::runTestSuite() {
    const TestConfig config; //Default values
    auto inferNearest = std::make_shared<PrimeFieldInferation::PrimeFieldInferationSchemeNearest>(PrimeFieldInferation::PrimeFieldInferationSchemeNearest());
    auto inferWeightedAverage = std::make_shared<PrimeFieldInferation::PrimeFieldInferationSchemeWeightedAverage>(PrimeFieldInferation::PrimeFieldInferationSchemeWeightedAverage());

    auto Euler = std::make_shared<BucherTableau::ExplicitButcherTableau<1>>(BucherTableau::ExplicitButcherTableau<1>::Euler());
    auto RK4 = std::make_shared<BucherTableau::ExplicitButcherTableau<4>>(BucherTableau::ExplicitButcherTableau<4>::RungeKutta4());
    auto RK3 = std::make_shared<BucherTableau::ExplicitButcherTableau<4>>(BucherTableau::ExplicitButcherTableau<4>::RungeKutta3());
    auto Heun = std::make_shared<BucherTableau::ExplicitButcherTableau<2>>(BucherTableau::ExplicitButcherTableau<2>::Heun());
    
    std::vector<std::shared_ptr<BucherTableau::IButcherTableau>> schemes = {Euler, RK4, RK3, Heun};
    std::vector<std::shared_ptr<PrimeFieldInferation::PrimeFieldInferationScheme>> inferationSchemes = {inferNearest, inferWeightedAverage};
    const std::vector<Structures::Point<double>> startPoints = {
        {1.5, 1.5}, {-1.5, -1.5}, {3, 1}, {-3, 1}, {5, 5}, {-5, -5}, {-5, 5}, {5, -5}, {10, -10}, {-10, 10}, {-7, 9}, {7, -9}
    };

    std::function<void(std::vector<Structures::Arrow<double>>, std::string)> runTestOnAllMethods = getRunner(schemes, inferationSchemes, startPoints, config);

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

    DynamicalSystem::DynamicalSystemKnownSoulution knownSoulution1 = DynamicalSystem::DynamicalSystemKnownSoulution(
        [](Structures::Point<double> start, double t) {
            return Structures::Point<double> {
                start.y * std::sin(t) + start.x * std::cos(t),
                -start.x * std::sin(t) + start.y * std::cos(t)
            };
        }
    );

    runTestOnAllMethods(functionPrimeField1, "Function (x, y) -> (y, -x)");

    std::vector<Structures::Arrow<double>> functionPrimeField2 = FieldGeneratorFunction(
        config.fieldDelta,
        config.window,
        [](Structures::Point<double> point) {
            return Structures::Point<double> {2*point.y + point.x, point.x + 3*point.y};
        }
    ).generateField();

    runTestOnAllMethods(functionPrimeField2, "Function (x, y) -> (2y + x, x + 3y)");

    std::vector<Structures::Arrow<double>> functionPrimeField3 = FieldGeneratorFunction(
        config.fieldDelta,
        config.window,
        [](Structures::Point<double> point) {
            return Structures::Point<double> {point.y, point.x};
        }
    ).generateField();

    runTestOnAllMethods(functionPrimeField3, "Function (x, y) -> (y, x)");
}

void ODE::Tests::storeTest(
    std::string name, 
    std::vector<Structures::Arrow<double>> primeField,
    std::vector<std::pair<std::vector<Trajectory>, std::string>> trajectories
) {
    Store::Store store (name);
    store.write("Prime field");
    store.store(primeField, "Prime");
    store.write("Trajectory 1");
    for (const auto& [trajectory, tag] : trajectories) {
        store.store(trajectory, tag);
    }
}

std::vector<ODE::Trajectory> ODE::Tests::TestIteration::test(std::vector<Structures::Point<double>> startPoints) {
    std::vector<Trajectory> trajectories;
    for (const auto& startPoint : startPoints) {
        Trajectory trajectory = Trajectory(startPoint);
        Structures::Point<double> point = startPoint;
        for (int i = 0; i < this->iterations; i++) {
            point = this->scheme.step(point, this->dt);
            trajectory.addPoint(point);
        }
        trajectories.push_back(trajectory);
    }  
    return trajectories;
}