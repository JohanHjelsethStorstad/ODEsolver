#include "TestIteration.h"
#include "FieldGenerator.h"
#include "../src/Store.h"
#include "../src/DynamicalSystem.h"
#include <memory>
#include <vector>
#include <iostream>

void ODE::Tests::FieldRunner::run(
    std::vector<Structures::Arrow<double>> primeField, 
    std::string fieldName, 
    const std::optional<std::shared_ptr<ODE::DynamicalSystem::DynamicalSystem>>& knownSolution
) {
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
    if (knownSolution.has_value()) {
        for (const auto& startPoint : startPoints) {
            auto trajectoryFunc = knownSolution->get()->getExactTrajectorySolution(startPoint);
            Trajectory trajectory = Trajectory(startPoint);
            Structures::Point<double> point = startPoint;
            for (int i = 1; i < config.iterations; i++) {
                point = trajectoryFunc(config.dt * i);
                trajectory.addPoint(point);
            }
            trajectories.push_back({{trajectory}, "Exact"});
        }
    }
    storeTest(fieldName, primeField, trajectories);
}

void ODE::Tests::runTestSuite(const std::string configFileName) {
    const TestConfig config; //Default values
    auto inferNearest = std::make_shared<PrimeFieldInferation::PrimeFieldInferationSchemeNearest>(PrimeFieldInferation::PrimeFieldInferationSchemeNearest());
    auto inferWeightedAverage = std::make_shared<PrimeFieldInferation::PrimeFieldInferationSchemeWeightedAverage>(PrimeFieldInferation::PrimeFieldInferationSchemeWeightedAverage());

    auto Euler = std::make_shared<BucherTableau::ExplicitButcherTableau<1>>(BucherTableau::ExplicitButcherTableau<1>::Euler());
    auto RK4 = std::make_shared<BucherTableau::ExplicitButcherTableau<4>>(BucherTableau::ExplicitButcherTableau<4>::RungeKutta4());
    auto RK3 = std::make_shared<BucherTableau::ExplicitButcherTableau<4>>(BucherTableau::ExplicitButcherTableau<4>::RungeKutta3());
    auto Heun = std::make_shared<BucherTableau::ExplicitButcherTableau<2>>(BucherTableau::ExplicitButcherTableau<2>::Heun());
    
    std::vector<std::shared_ptr<BucherTableau::ButcherTableau>> schemes = {RK4};
    std::vector<std::shared_ptr<PrimeFieldInferation::PrimeFieldInferationScheme>> inferationSchemes = {inferNearest, inferWeightedAverage};
    const std::vector<Structures::Point<double>> startPoints = {
        {1.5, 1.5}, {-1.5, -1.5}, {3, 1}, {-3, 1}, {-7, 9}, {7, -9}
    };

    FieldRunner fieldRunner = FieldRunner(schemes, inferationSchemes, startPoints, config);

    std::vector<Structures::Arrow<double>> randomPrimeField = FieldGeneratorRandom(
        config.fieldDelta, 
        config.window,
        config.bounds
    ).generateField();

    fieldRunner.run(randomPrimeField, "Random", std::nullopt);

    std::vector<Structures::Arrow<double>> functionPrimeField1 = FieldGeneratorFunction(
        config.fieldDelta,
        config.window,
        [](Structures::Point<double> point) {
            return Structures::Point<double> {point.y, -point.x};
        }
    ).generateField();

    std::shared_ptr<DynamicalSystem::DynamicalSystemKnownSoulution> knownSoulution1 = std::make_shared<DynamicalSystem::DynamicalSystemKnownSoulution>(
        [](Structures::Point<double> start, double t) {
            return Structures::Point<double> {
                start.y * std::sin(t) + start.x * std::cos(t),
                -start.x * std::sin(t) + start.y * std::cos(t)
            };
        }
    );

    fieldRunner.run(functionPrimeField1, "Function (x, y) -> (y, -x)", knownSoulution1);

    std::vector<Structures::Arrow<double>> functionPrimeField2 = FieldGeneratorFunction(
        config.fieldDelta,
        config.window,
        [](Structures::Point<double> point) {
            return Structures::Point<double> {2*point.y + point.x, point.x + 3*point.y};
        }
    ).generateField();

    fieldRunner.run(functionPrimeField2, "Function (x, y) -> (2y + x, x + 3y)", std::nullopt);

    std::vector<Structures::Arrow<double>> functionPrimeField3 = FieldGeneratorFunction(
        config.fieldDelta,
        config.window,
        [](Structures::Point<double> point) {
            return Structures::Point<double> {point.y, point.x};
        }
    ).generateField();

    std::shared_ptr<DynamicalSystem::DynamicalSystemKnownSoulution> knownSoulution3 = std::make_shared<DynamicalSystem::DynamicalSystemKnownSoulution>(
        [](Structures::Point<double> start, double t) {
            double c1 = ( start.x + start.y ) / 2;
            double c2 = ( start.x - start.y ) / 2;
            return Structures::Point<double> {
                c1 * std::exp(t) + c2 * std::exp(-t),
                c1 * std::exp(t) - c2 * std::exp(-t)
            };
        }
    );

    fieldRunner.run(functionPrimeField3, "Function (x, y) -> (y, x)", knownSoulution3);
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