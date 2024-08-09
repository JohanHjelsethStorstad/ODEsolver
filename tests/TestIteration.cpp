#include "TestIteration.h"
#include "FieldGenerator.h"
#include "../src/Store.h"
#include "../src/DynamicalSystem.h"
#include <memory>
#include <vector>
#include <iostream>
#include "../src/ODE.h"

void ODE::Tests::FieldRunner::run(
    std::vector<Structures::Arrow<double>> primeField, 
    std::string fieldName, 
    const std::optional<std::shared_ptr<DynamicalSystem::DynamicalSystem>>& knownSolution
) {
    std::vector<std::pair<std::vector<Trajectory>, std::string>> trajectories;
    for (const auto& scheme : config.schemes) {
        for (const auto& inferationScheme : config.inferationSchemes) {
            trajectories.push_back({TestIteration(IterationScheme(
                primeField,
                scheme,
                inferationScheme
            ), config.dt, config.iterations).test(config.startPoints), scheme->getName() + " " + inferationScheme->getName()});
        }
    }
    if (knownSolution.has_value()) {
        for (const auto& startPoint : config.startPoints) {
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
    const Config::TestConfig config = Config::TestConfig().loadFromFile(configFileName);

    FieldRunner fieldRunner = FieldRunner(config);
    
    std::vector<Structures::Arrow<double>> primeField;
    switch (config.fieldGeneratorInfo.type) {
        case Config::FieldGeneratorType::RANDOM:
            primeField = FieldGeneratorRandom(
                config.fieldDelta,
                config.window,
                config.fieldGeneratorInfo.bounds
            ).generateField();
            break;
        case Config::FieldGeneratorType::FUNCTION:
            primeField = FieldGeneratorFunction(
                config.fieldDelta,
                config.window,
                config.fieldGeneratorInfo.preProgrammedODE
            ).generateField();
            break;
        case Config::FieldGeneratorType::LOAD_FROM_FILE:
            primeField = FieldGeneratorFromFile(
                config.fieldGeneratorInfo.fileName
            ).generateField();
            break;
    }
    fieldRunner.run(primeField, configFileName, config.knownSolution);
}

void ODE::Tests::storeTest(
    std::string name, 
    std::vector<Structures::Arrow<double>> primeField,
    std::vector<std::pair<std::vector<Trajectory>, std::string>> trajectories
) {
    Store::Store store = Store::Stores::testStore(name);
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