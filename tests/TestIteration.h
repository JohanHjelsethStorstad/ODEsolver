#pragma once
#include "../src/IterationScheme.h"
#include "../src/Structures.h"
#include "FieldGenerator.h"
#include <vector>
#include <string>
#include "../src/Trajectory.h"

namespace ODE::Tests {
    void runTestSuite();
    void storeTest(std::string name, std::vector<Structures::Arrow<double>> primeField, std::vector<std::pair<std::vector<Trajectory>, std::string>> trajectories);

    struct TestConfig {
        static constexpr int iterations = 1000;
        static constexpr double dt = 0.2;

        static constexpr double fieldDelta = 0.1;
        static constexpr FieldGeneratorWindow window = {20, 20, -10, -10};

        static constexpr FieldGeneratorRandomBounds bounds = {-10, 10};
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
}