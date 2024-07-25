#pragma once
#include <vector>
#include "Structures.h"

namespace ODE::PrimeFieldInferation {
    class PrimeFieldInferationScheme {
    public:
        virtual Structures::Arrow<double> infer(const std::vector<Structures::Arrow<double>>& discreetField, Structures::Point<double> point) = 0;
    };

    class PrimeFieldInferationSchemeNearest : public PrimeFieldInferationScheme {
    public:
        Structures::Arrow<double> infer(const std::vector<Structures::Arrow<double>>& discreetField, Structures::Point<double> point) override;
    };

    class PrimeFieldInferationSchemeWeightedAverage : public PrimeFieldInferationScheme {
    public:
        Structures::Arrow<double> infer(const std::vector<Structures::Arrow<double>>& discreetField, Structures::Point<double> point) override;
    };
};