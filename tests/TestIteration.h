#pragma once
#include "../src/IterationScheme.h"
#include "../src/structures/Point.h"
#include "../src/structures/Arrow.h"
#include "FieldGenerator.h"
#include <vector>
#include <string>
#include <functional>
#include "../src/Trajectory.h"

namespace ODE::Tests {
    struct TestConfig {
        int iterations = 1000;
        double dt = 0.2;

        double fieldDelta = 0.1;
        FieldGeneratorWindow window = {20, 20, -10, -10};

        FieldGeneratorRandomBounds bounds = {-10, 10};
    };

    class TestIteration {
    private:
        IterationScheme scheme;
        double dt;
        int iterations = 100;
    public:
        TestIteration(IterationScheme scheme, double dt, int iterations) : scheme(scheme), dt(dt), iterations(iterations) {}
        std::vector<Trajectory> test(std::vector<Structures::Point<double>> startPoints = {{1.5, 1.5}});
    };

    void runTestSuite();
    std::function<void(std::vector<Structures::Arrow<double>>, std::string)> getRunner(
        const std::vector<std::shared_ptr<BucherTableau::IButcherTableau>>& schemes,
        const std::vector<std::shared_ptr<PrimeFieldInferation::PrimeFieldInferationScheme>>& inferationSchemes,
        const std::vector<Structures::Point<double>>& startPoints,
        const TestConfig& config
    );
    void storeTest(std::string name, std::vector<Structures::Arrow<double>> primeField, std::vector<std::pair<std::vector<Trajectory>, std::string>> trajectories);
}