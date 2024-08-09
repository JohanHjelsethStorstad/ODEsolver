#pragma once
#include "../src/IterationScheme.h"
#include "../src/structures/Point.h"
#include "../src/structures/Arrow.h"
#include "FieldGenerator.h"
#include <vector>
#include <string>
#include <functional>
#include <optional>
#include "../src/Trajectory.h"
#include "../src/DynamicalSystem.h"
#include "TestConfig.h"

namespace ODE::Tests {
    class TestIteration {
    private:
        IterationScheme scheme;
        double dt;
        int iterations = 100;
    public:
        TestIteration(IterationScheme scheme, double dt, int iterations) : scheme(scheme), dt(dt), iterations(iterations) {}
        std::vector<Trajectory> test(std::vector<Structures::Point<double>> startPoints = {{1.5, 1.5}});
    };

    void runTestSuite(const std::string configFileName);
    void storeTest(std::string name, std::vector<Structures::Arrow<double>> primeField, std::vector<std::pair<std::vector<Trajectory>, std::string>> trajectories);

    class FieldRunner {
    private:
        Config::TestConfig config;
    public:
        FieldRunner(
            const Config::TestConfig& config
        ) : config(config) {}

        void run(
            std::vector<Structures::Arrow<double>> primeField, 
            std::string fieldName,
            const std::optional<std::shared_ptr<DynamicalSystem::DynamicalSystem>>& knownSolution
        );
    };
}