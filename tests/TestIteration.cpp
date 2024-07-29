#include "TestIteration.h"
#include "FieldGenerator.h"
#include "Plot.h"
#include <memory>
#include <vector>
#include <iostream>

void ODE::Tests::runTestSuite() {
    static constexpr int iterations = 1000;
    static constexpr double dt = 0.01;

    static constexpr double fieldDelta = 0.1;
    static constexpr double width = 10;
    static constexpr double height = 10;
    static constexpr FieldGeneratorRandomBounds bounds = {0, 10};

    std::vector<Structures::Arrow<double>> primeField = FieldGeneratorRandom(fieldDelta, width, height, bounds).generateField();
    std::cout << primeField << std::endl;
    //Plot::plotArrows(primeField);
    IterationScheme scheme = IterationScheme(
        primeField,
        std::make_shared<BucherTableau::ExplicitButcherTableau<1>>(BucherTableau::ExplicitButcherTableau<1>::Euler()),
        std::make_shared<PrimeFieldInferation::PrimeFieldInferationSchemeNearest>(PrimeFieldInferation::PrimeFieldInferationSchemeNearest())
    );

    TestIteration testIteration = TestIteration(scheme, dt, iterations);
    const std::vector<Structures::Point<double>> result = testIteration.test();

    Plot::show();
}

std::vector<Structures::Point<double>> ODE::Tests::TestIteration::test() {
    std::vector<Structures::Point<double>> points;
    Structures::Point<double> point = {0, 0};
    for (int i = 0; i < this->iterations; i++) {
        point = this->scheme.step(point, this->dt);
        points.push_back(point);
    }
    return points;
}