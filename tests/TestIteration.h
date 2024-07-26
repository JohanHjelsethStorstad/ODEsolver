#pragma once
#include "IterationScheme.h"
#include "Structures.h"
#include <vector>

namespace ODE::Tests {
    template <int iterations>
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