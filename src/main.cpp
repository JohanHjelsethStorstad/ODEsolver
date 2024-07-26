#include "IterationScheme.h"
#include <memory>

/**
 * @brief Main function - Example of usage of the IterationScheme class
 */
int main() {
    std::shared_ptr<ODE::BucherTableau::IButcherTableau> butcherTableau = std::make_shared<ODE::BucherTableau::ExplicitButcherTableau<1>>(
        ODE::BucherTableau::ExplicitButcherTableau<1>::Euler()
    );
    std::shared_ptr<ODE::PrimeFieldInferation::PrimeFieldInferationScheme> inferationScheme = std::make_shared<ODE::PrimeFieldInferation::PrimeFieldInferationSchemeNearest>();
    std::vector<Structures::Arrow<double>> primeField = {
        { {0, 0}, {1, 1} },
        { {1, 1}, {2, 2} },
        { {2, 2}, {3, 3} },
        { {3, 3}, {4, 4} },
        { {4, 4}, {5, 5} }
    };
    ODE::IterationScheme iterationScheme(primeField, butcherTableau, inferationScheme);

    std::vector<Structures::Point<double>> points;
    points.push_back({ 0.5, 0.5 });
    static constexpr int N = 1000;
    static constexpr double dt = 0.01;
    for (int i = 0; i < N; i++) {
        points.push_back(iterationScheme.step(points.back(), dt));
    }

    return 0;
}