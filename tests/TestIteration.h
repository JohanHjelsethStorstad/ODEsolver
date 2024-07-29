#pragma once
#include "../src/IterationScheme.h"
#include "../src/Structures.h"
#include <vector>
#include "../lib/matplotlib-cpp/matplotlibcpp.h"

namespace ODE::Tests {
    void runTestSuite();

    class TestIteration {
    private:
        IterationScheme scheme;
        double dt;
        int iterations = 100;
    public:
        TestIteration(IterationScheme scheme, double dt, int iterations) : scheme(scheme), dt(dt), iterations(iterations) {}
        std::vector<Structures::Point<double>> test();
    };
}